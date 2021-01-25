/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_errrange.h"

Test_ErrRange::Test_ErrRange(QObject *parent) : Test_Object(parent)
{

}

void Test_ErrRange::initFunSlot()
{
    mSourceDev = mPacket->getDev(0);
}

Test_ErrRange *Test_ErrRange::bulid(QObject *parent)
{
    static Test_ErrRange* sington = nullptr;
    if(sington == nullptr)
        sington = new Test_ErrRange(parent);
    return sington;
}

bool Test_ErrRange::volErr(int id)
{
    int pass = Test_Fail;
    int err = mItem->err.volErr;
    int value = mDev->line.vol.value[id];
    int exValue = mSourceDev->line.vol.value[id];
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.vol.status[id] = pass;

    return ret;
}

bool Test_ErrRange::curErr(int id)
{
    int pass = Test_Fail;
    int err = mItem->err.curErr+1;
    int value = mDev->line.cur.value[id];
    int exValue = mSourceDev->line.cur.value[id];

    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.cur.status[id] = pass;

    return ret;
}


bool Test_ErrRange::oneLineVolErr()
{
    int pass = Test_Fail;
    int err = 2*mItem->err.volErr+1;
    ushort *ptr = mDev->line.vol.value;
    int exValue = 2*ptr[0];
    int value = ptr[1] + ptr[2];
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.vol.status[0] = pass;

    return ret;
}

bool Test_ErrRange::oneLineCurErr()
{
    int pass = Test_Fail;
    int err = 2*mItem->err.curErr+1;
    ushort *ptr = mDev->line.cur.value;
    int exValue = ptr[0];
    int value = ptr[1] + ptr[2];

    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.cur.status[0] = pass;

    return ret;
}


bool Test_ErrRange::oneLinePowErr()
{
    int pass = Test_Fail;
    ushort *ptr = mDev->line.pow;
    int exValue = ptr[0];
    int value = ptr[1] + ptr[2];
    int err = exValue * (2*mItem->err.powErr+1)/1000.0;
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.powStatus[0] = pass;

    return ret;
}

bool Test_ErrRange::powErr(int id)
{
    int pass = Test_Fail;
    int value = mDev->line.pow[id];
    int exValue = mSourceDev->line.pow[id];
    int err = exValue * (mItem->err.powErr+1)/1000.0;

    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.powStatus[id] = pass;

    return ret;
}

bool Test_ErrRange::temErr()
{
    int pass = Test_Fail;
    int exValue = mSourceDev->env.tem.value[0];
    int value = mDev->env.tem.value[0];
    bool ret = checkErrRange(exValue, value, 5);
    if(ret) pass = Test_Pass;
    mDev->env.tem.status[0] = pass;

    return ret;
}

bool Test_ErrRange::humErr()
{
    int pass = Test_Fail;
    int exValue = mSourceDev->env.hum.value[0];
    int value = mDev->env.hum.value[0];
    bool ret = checkErrRange(exValue, value, 10);
    if(ret) pass = Test_Pass;
    mDev->env.hum.status[0] = pass;

    return ret;
}

bool Test_ErrRange::checkErrRange(int exValue, int value, int err)
{
    bool ret = false;
    int min = exValue - err;
    int max = exValue + err;
    if((value>=min) && (value<=max) && value) {
        ret =  true;
    } else {
        qDebug() << "value Err Range" << value << exValue << err;
    }

    return ret;
}

bool Test_ErrRange::volAlarm(int id)
{
    sCfgDev *cth = &(mItem->cTh);
    sDataUnit *unit = &(mDev->line.vol);

    bool ret = true;
    if(unit->min[id] != cth->vol_min) ret = false;
    if(unit->max[id] != cth->vol_max) ret = false;

    return ret;
}

bool Test_ErrRange::curAlarm(int id)
{
    sCfgDev *cth = &(mItem->cTh);
    sDataUnit *unit = &(mDev->line.cur);

    bool ret = true;
    if((mDt->lines == 2) && id){
        if(unit->min[id]/10 != (cth->cur_min/10+1)/2) ret = false;
        if(unit->max[id]/10 != (cth->cur_max/10+1)/2) ret = false;
    }else{
        if(unit->min[id] != cth->cur_min) ret = false;
        if(unit->max[id] != cth->cur_max) ret = false;
    }

    return ret;
}


bool Test_ErrRange::temAlarm()
{
    bool ret = true;
    sDataUnit *unit = &(mDev->env.tem);
    if(unit->max[0] > 60) ret = false;
    if(unit->min[0]) ret = false;

    return ret;
}


bool Test_ErrRange::humAlarm()
{
    bool ret = true;
    sDataUnit *unit = &(mDev->env.hum);
    if(unit->max[0] > 99) ret = false;
    if(unit->min[0]) ret = false;

    return ret;
}
