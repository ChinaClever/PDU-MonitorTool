/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "ctrl_sirtu.h"

Ctrl_SiRtu::Ctrl_SiRtu(QObject *parent) : Dev_Object(parent)
{

}

bool Ctrl_SiRtu::readPduData()
{
    return Dev_SiRtu::bulid(this)->readPduData();
}


// 表示行业标准 Modbus RTU 模式
bool Ctrl_SiRtu::setModel()
{
    sRtuSetItem it;
    it.addr = mDev->id;
    it.fn = 0x06;
    it.reg = 0x1019;
    it.data = 1;

    return mModbus->write(it);
}


bool Ctrl_SiRtu::funClearEle()
{
    return sentRtuCmd(0x1013, 0xFF00);
}

bool Ctrl_SiRtu::sentRtuCmd(ushort reg, ushort value)
{
    sRtuSetItem it;
    it.addr = mDev->id;
    it.fn = 0x10;
    it.reg = reg;
    it.data = value;

    return mModbus->write(it);
}
