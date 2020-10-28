/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "ctrl_iprtu.h"

Ctrl_IpRtu::Ctrl_IpRtu(QObject *parent) : Ctrl_Object(parent)
{
    mRtu = Dev_IpRtu::bulid(this);
}

Ctrl_IpRtu *Ctrl_IpRtu::bulid(QObject *parent)
{
    static Ctrl_IpRtu* sington = nullptr;
    if(sington == nullptr)
        sington = new Ctrl_IpRtu(parent);
    return sington;
}

bool Ctrl_IpRtu::readPduData()
{
    return mRtu->readPduData();
}

bool Ctrl_IpRtu::setCurTh(int i)
{
    bool ret = true;
    ushort reg = 0x1008 + 2*i;
    sDataUnit *unit = &(mDev->line.cur);

    ushort value = mItem->cTh.cur_min;
    if(unit->min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = mItem->cTh.cur_max;
    if(unit->max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    return ret;
}

bool Ctrl_IpRtu::setVolTh(int i)
{
    bool ret = true;
    ushort reg = 0x1002 + 2*i;
    sDataUnit *unit = &(mDev->line.vol);

    ushort value = mItem->cTh.vol_min;
    if(unit->min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = mItem->cTh.vol_max;
    if(unit->max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    return ret;
}


bool Ctrl_IpRtu::sentRtuCmd(ushort reg, ushort value)
{
    sRtuSetItem it;
    it.addr = mDev->id;
    if(mDt->version == 3) {
        it.fn = 0x06; //V3 写 0x06
    } else{
        it.fn = 0x10;//V1 写 0x10
    }

    it.reg = reg;
    it.data = value;
    return mModbus->write(it);
}
