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


bool Ctrl_SiRtu::setAcTh()
{
    bool ret = true;
    ushort reg = 0x1002;

//    for(int i=0; i<mData->size; ++i) {

//        ushort value = mItem->cTh.vol_max;
//        if(mData->volTh.max[i] != value) {

//            ret = sentRtuCmd(reg++, value);
//            if(!ret) return ret;
//        } else reg++;

//        value = mItem->cTh.vol_min;
//        if(mData->volTh.min[i] != value) {


//            ret = sentRtuCmd(reg++, value);
//            if(!ret) return ret;
//        } else reg++;
//    }

//    reg = 0x1008;
//    for(int i=0; i<mData->size; ++i) {
//        ushort value = mItem->cTh.cur_max;
//        if(mData->curTh.max[0] != value) {


//            ret = sentRtuCmd(reg++, value);
//            if(!ret) return ret;
//        } else reg++;

//        value = mItem->cTh.cur_min;
//        if(mData->curTh.min[0] != value) {
//            ret = sentRtuCmd(reg++, value);
//            if(!ret) return ret;
//        } else reg++;
//    }

    return ret;
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
