/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "ctrl_sirtu.h"

Ctrl_SiRtu::Ctrl_SiRtu(QObject *parent) : Ctrl_Object(parent)
{
}

Ctrl_SiRtu *Ctrl_SiRtu::bulid(QObject *parent)
{
    static Ctrl_SiRtu* sington = nullptr;
    if(sington == nullptr)
        sington = new Ctrl_SiRtu(parent);
    return sington;
}

bool Ctrl_SiRtu::setCurTh(int i)
{
    bool ret = true;
    ushort reg = 0x1008 + 2*i;
    if(DC == mDt->ac) reg = 0x1016;

    sDataUnit *unit = &(mDev->line.cur);
    ushort value = mItem->cTh.cur_max;
    if((mDt->lines == 2) && i) value = (value/10 +1)/2 * 10; // 解决单项二路阈值问题
    if(unit->max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = mItem->cTh.cur_min;
    if(unit->min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    return ret;
}

bool Ctrl_SiRtu::setVolTh(int i)
{
    bool ret = true;
    ushort reg = 0x1002 + 2*i;
    if(DC == mDt->ac) reg = 0x1014;

    sDataUnit *unit = &(mDev->line.vol);
    ushort value = mItem->cTh.vol_max;
    if(unit->max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = mItem->cTh.vol_min;
    if(unit->min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

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

bool Ctrl_SiRtu::factorySet()
{
    return sentRtuCmd(0x1013, 0xFF00); // 清除电能
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
