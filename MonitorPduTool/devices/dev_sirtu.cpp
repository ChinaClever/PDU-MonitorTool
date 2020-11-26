/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_sirtu.h"

#define SI_RTU_DC_LEN 0x1B // 直流数据长度
#define SI_RTU_THREE_LEN 0x51  // 三相数据长度//单相时，L2和L3表示C1和C2

Dev_SiRtu::Dev_SiRtu(QObject *parent) : Dev_Object(parent)
{

}

Dev_SiRtu *Dev_SiRtu::bulid(QObject *parent)
{
    static Dev_SiRtu* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_SiRtu(parent);
    return sington;
}


void Dev_SiRtu::initRtuItem(sRtuItem &it)
{
    it.addr = mDev->id;
    it.fn = 0x03;
    it.reg = 0;
    it.num = SI_RTU_THREE_LEN;

    uchar res = mDev->devType.ac;
    if(DC == res) {
        it.num = SI_RTU_DC_LEN;
    } else if(mItem->cTh.si_mod) {
        it.num /= 2;  // 特殊定制
    }
}


/**
  * 功　能：长度 校验
  * 入口参数：buf -> 缓冲区  len -> 长度
  * 返回值：0 正确
  */
int Dev_SiRtu::recvLine(int len)
{
    int ret = 0;
    switch (len) {
    case SI_RTU_DC_LEN: ret = 1; break;
    case SI_RTU_THREE_LEN: ret = 3; break;
    default: qDebug() << "SI rtu recv len Err!!" << len; break;
    }

    return ret;
}


int Dev_SiRtu::recvDcData(uchar *ptr, int line)
{
    sObjData *obj = &(mDev->line);
    ptr = toShort(ptr, line, obj->vol.value);
    ptr = toShort(ptr, line, obj->cur.value);
    ptr = toShort(ptr, line, obj->pow);

    ptr = toInt(ptr, line, obj->ele);
    ptr = toThreshold(ptr, line, obj->vol);
    ptr = toThreshold(ptr, line, obj->cur);

    sEnvData *env = &(mDev->env);
    env->tem.value[0] = *ptr++; env->tem.max[0] = 99;
    env->hum.value[0] = *ptr++; env->hum.max[0] = 99;
    env->size = env->tem.size = env->hum.size = 1;

    mDev->br = *(ptr++); // 波特率
    ptr = toShort(ptr, line, obj->aPow);
    ptr = toChar(ptr, line, obj->pf); // 功率因数
    ptr = toChar(ptr, line, obj->sw); // 开关状态
    obj->size = *(ptr++);
    mDev->hz = *(ptr++);

    if(obj->size == 0)  obj->size = 1;
    obj->vol.size = obj->cur.size = obj->size;

    return SI_RTU_DC_LEN;
}



/**
  * 功　能：读取电参数 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
int Dev_SiRtu::recvAcData(uchar *ptr, int line)
{
    sObjData *obj = &(mDev->line);
    ptr = toShort(ptr, line, obj->vol.value);
    ptr = toShort(ptr, line, obj->cur.value);
    ptr = toShort(ptr, line, obj->pow);

    ptr = toInt(ptr, line, obj->ele);
    ptr = toThreshold(ptr, line, obj->vol);
    ptr = toThreshold(ptr, line, obj->cur);

    sEnvData *env = &(mDev->env);
    env->size = env->tem.size = env->hum.size = 1;
    env->tem.value[0] = *ptr++;
    env->hum.value[0] = *ptr++;

    ptr = toEnvTh(ptr, env->tem);
    ptr = toEnvTh(ptr, env->hum);

    obj->size = *(ptr++);
    mDev->br = *(ptr++); // 波特率
    ptr = toShort(ptr, line, obj->aPow);
    ptr = toChar(ptr, line, obj->pf); // 功率因数
    ptr = toChar(ptr, line, obj->sw); // 开关状态
    ptr += 3;
    mDev->hz = *(ptr++);

    mDt->lines = obj->size;
    if(obj->size > 1)  obj->size = 3;
    obj->vol.size = obj->cur.size = obj->size;

    return SI_RTU_THREE_LEN;
}



bool Dev_SiRtu::recvPacket(uchar *buf, int len)
{
    bool ret = true;
    int line = recvLine(len);
    switch (line) {
    case 1: recvDcData(buf, line); break;
    case 3: recvAcData(buf, line); break;
    default: ret = false; break;
    }

    return ret;
}

bool Dev_SiRtu::readPduData()
{
    sRtuItem it;
    uchar recv[MODBUS_RTU_SIZE] = {0};

    initRtuItem(it);
    int len = mModbus->read(it, recv);
    return recvPacket(recv, len);
}
















