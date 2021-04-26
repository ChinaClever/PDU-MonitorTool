/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_object.h"

Dev_Object::Dev_Object(QObject *parent) : QThread(parent)
{
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();
    mDev = mPacket->getDev();
    mDt = &(mDev->devType);
    QTimer::singleShot(850,this,SLOT(initFunSlot()));
}

void Dev_Object::initFunSlot()
{
    setModbus(2);
}

void Dev_Object::setModbus(int id)
{
    mModbus = Rtu_Modbus::bulid(this)->get(id);
}

uchar *Dev_Object::toInt(uchar *ptr, int line, uint *value)
{
    for(int i=0; i<line; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
        value[i] <<= 16; // 左移8位
        value[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
    }

    return ptr;
}

uchar *Dev_Object::toOutputEle(uchar *ptr, int line, uint *value)
{
    for(int i=0; i<line; ++i) {
        value[i] = (*ptr++) << 16;
        value[i] += (*ptr++) << 8;
        value[i] += *ptr++;
    }

    return ptr;
}

uchar *Dev_Object::toShort(uchar *ptr, int line, ushort *value)
{
    for(int i=0; i<line; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

uchar *Dev_Object::toChar(uchar *ptr, int line, uchar *value)
{
    for(int i=0; i<line; ++i) {
        value[i] = *(ptr++); // 读取电压
    }

    return ptr;
}

uchar *Dev_Object::toThreshold(uchar *ptr, int line, sDataUnit &unit)
{
    for(int i=0; i<line; ++i) {
        ptr = toShort(ptr, 1, &unit.min[i]);
        ptr = toShort(ptr, 1, &unit.max[i]);
    }

    return ptr;
}

uchar *Dev_Object::toEnvTh(uchar *ptr, sDataUnit &unit)
{
    unit.max[0] = *ptr++;
    unit.min[0] = *ptr++;
    return ptr;
}

ushort Dev_Object::getShort(uchar *ptr)
{
    return  (*ptr) * 256 + *(ptr+1);
}

uchar *Dev_Object::getShort(uchar *ptr, int line, uchar *value)
{
    for(int i=0; i<line; ++i) {
        value[i] = getShort(ptr); ptr += 2;
    }

    return  ptr;
}
