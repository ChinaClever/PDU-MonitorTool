/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_source.h"

Dev_Source::Dev_Source(QObject *parent) : Dev_IpRtu(parent)
{
    mDev = sDataPacket::bulid()->getDev(0);
    init();
}

Dev_Source *Dev_Source::bulid(QObject *parent)
{
    static Dev_Source* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_Source(parent);
    return sington;
}

void Dev_Source::initFunSlot()
{
    mModbus = Rtu_Modbus::bulid(this)->get(0);
}


void Dev_Source::init()
{
    mDev->id = 1;
    sDevType *dev = &(mDev->devType);
    dev->version = 3; //
}

bool Dev_Source::read()
{
    bool ret = readPduData();
    if(!ret) ret = readPduData();
    if(!ret) {
        QString str = tr("比对源IP-PDU数据读取失败，结束测试");
        mPacket->updatePro(str, ret);
    }

    return ret;
}
