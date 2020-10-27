/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_object.h"

Test_Object::Test_Object(QObject *parent) : QThread(parent)
{
    isRun = false;
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();
    mDev = mPacket->getDev();
    mDt = &(mDev->devType);
    QTimer::singleShot(500,this,SLOT(initFunSlot()));
}

Test_Object::~Test_Object()
{
    isRun = false;
    wait();
}
