/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_source.h"

Dev_Source::Dev_Source(QObject *parent) : Dev_SiRtu(parent)
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
    setModbus(0);
}


void Dev_Source::init()
{
    mDev->id = 1;
    sDevType *dev = &(mDev->devType);
    dev->version = 1; //
}

bool Dev_Source::read()
{
    bool ret = true;
    //mDev->devType.ac = mItem->si.ac;
    for(int i=0; i<3; ++i) {
        ret = readPduData();
        if(ret) break; else mModbus->changeBaudRate();
    }

    if(!ret) {
        QString str = tr("比对源SI-PDU数据读取失败，结束测试");
        mPacket->updatePro(str, ret);
    }

    return ret;
}
