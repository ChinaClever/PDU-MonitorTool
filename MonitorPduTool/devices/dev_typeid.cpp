/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_typeid.h"

Dev_TypeId::Dev_TypeId(QObject *parent) : QThread(parent)
{
    mItem = Cfg::bulid()->item;
    mPacket = sDataPacket::bulid();
    mPro = mPacket->getPro();
    mDev = mPacket->getDev();
    mTypeDef = Dev_TypeDef::bulid();
    mModbus = Rtu_Modbus::bulid(this)->get();
}

Dev_TypeId *Dev_TypeId::bulid(QObject *parent)
{
    static Dev_TypeId* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_TypeId(parent);
    return sington;
}

void Dev_TypeId::initReadType(sRtuItem &it)
{
    it.addr = mDev->id;
    it.fn = 0x03;
    it.reg = 0xA001;
    it.num = 2;
}

bool Dev_TypeId::analysDevType(uchar *buf, int len)
{
    bool ret = false;
    QString str = tr("读取设备序列号成功");
    if(len != 4) {
        str = tr("读取设备序列号失败：返回长度为%1").arg(len);
        return mPacket->updatePro(str, ret);
    }

    uint id = 0;
    for(int i=0; i<len; ++i) {
        id *= 256;  id += buf[i];
    }

    ret = mTypeDef->analysDevType(id);
    if(!ret){
        str = tr("不支持此设备类型 ID：%1").arg(id);
    }

    return mPacket->updatePro(str, ret);
}

bool Dev_TypeId::readDevId()
{
    sRtuItem it;
    initReadType(it);

    uchar recv[8] = {0};
    int len = mModbus->read(it, recv);
    if(!len){ mPacket->delay(1); len = mModbus->read(it, recv); }
    if(0 == len){
        bool ret = mModbus->changeBaudRate(); // 自动转变波特泫
        if(!ret) len = mModbus->read(it, recv);
        if(!len) mModbus->changeBaudRate();
    }

    return analysDevType(recv, len);
}

bool Dev_TypeId::readDevType()
{
    mDev->devType.dev_type[0] = 0;
    QString str = tr("开始识别设备类型！");
    bool ret = mPacket->updatePro(str, true, 3);
    if(ret) {
        ret = readDevId();
    }

    return ret;
}
