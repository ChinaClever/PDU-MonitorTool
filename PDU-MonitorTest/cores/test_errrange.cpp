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
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    int err = mItem->err.volErr*crate;
    int value = mDev->line.vol.value[id];
    int exValue = mSourceDev->line.vol.value[id]*crate;
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.vol.status[id] = pass;

    return ret;
}

bool Test_ErrRange::curErr(int id)
{
    int pass = Test_Fail;
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    int err = (mItem->err.curErr+1)*crate;
    int value = mDev->line.cur.value[id];
    int exValue = mSourceDev->line.cur.value[id]*crate;

    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.cur.status[id] = pass;

    return ret;
}


bool Test_ErrRange::oneLineVolErr()
{
    int pass = Test_Fail;
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    int err = (2*mItem->err.volErr+1)*crate;
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
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    int err = (2*mItem->err.curErr+1)*crate;
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
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    ushort *ptr = mDev->line.pow;
    int exValue = ptr[0];
    int value = ptr[1] + ptr[2];
    int err = exValue * (2*mItem->err.powErr+1);
    if(crate == 10)
    {
        if(mDev->devType.devType == SI_PDU) err /= 100.0;
        else err /= 1000.0;
        //if(mDev->devType.devType == IP_PDU) value /= 10;
    }
    else err /= 1000.0;
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.powStatus[0] = pass;

    return ret;
}

bool Test_ErrRange::oneLineECCVolErr()
{
    int pass = Test_Fail;
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    int err = (2*mItem->err.volErr+1)*crate;
    ushort *ptr = mDev->line.vol.value;
    ushort *ptr1 = mSour->line.vol.value;
    int exValue = 2*ptr[0];
    int value = ptr1[1] + ptr1[2];
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.vol.status[0] = pass;

    return ret;
}

bool Test_ErrRange::oneLineECCCurErr()
{
    int pass = Test_Fail;
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    int err = (2*mItem->err.curErr+1)*crate;
    ushort *ptr = mDev->line.cur.value;
    ushort *ptr1 = mSour->line.cur.value;
    int exValue = ptr[0];
    int value = ptr1[1] + ptr1[2];

    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.cur.status[0] = pass;

    return ret;
}


bool Test_ErrRange::oneLineECCPowErr()
{
    int pass = Test_Fail;
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    ushort *ptr = mDev->line.pow;
    ushort *ptr1 = mSour->line.pow;
    int exValue = ptr[0];
    int value = ptr1[1] + ptr1[2];
    int err = exValue * (2*mItem->err.powErr+1);
    if(crate == 10)
    {
        if(mDev->devType.devType == SI_PDU) err /= 100.0;
        else err /= 1000.0;
        //if(mDev->devType.devType == IP_PDU) value /= 10;
    }
    else err /= 1000.0;
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.powStatus[0] = pass;

    return ret;
}

bool Test_ErrRange::powErr(int id)
{
    int pass = Test_Fail;
    int crate = 1;
    if(mDev->devType.screen == 1) crate = 10;
    int value = mDev->line.pow[id]*crate;
    int exValue = mSourceDev->line.pow[id];
    int err = exValue * (mItem->err.powErr+1);
    if(crate == 10)
    {
        if(mDev->devType.devType == SI_PDU) err /= 100.0;
        else err /= 1000.0;
        if(mDev->devType.devType == IP_PDU) value /= 10;
    } else err /= 1000.0;
    bool ret = checkErrRange(exValue, value, err);
    if(ret) pass = Test_Pass;
    mDev->line.powStatus[id] = pass;

    return ret;
}

bool Test_ErrRange::temErr()
{
    int pass = Test_Fail;
    //int exValue = mSourceDev->env.tem.value[0];
    int value = mDev->env.tem.value[0];
    bool ret = false; if((value>0)&&(value<1000))ret=true;
    //bool ret = checkErrRange(exValue, value, 10);
    if(ret) pass = Test_Pass;
    mDev->env.tem.status[0] = pass;

    return ret;
}

bool Test_ErrRange::humErr()
{
    int pass = Test_Fail;
    //int exValue = mSourceDev->env.hum.value[0];
    int value = mDev->env.hum.value[0];
    bool ret = false; if((value>0)&&(value<1000))ret=true;
    //bool ret = checkErrRange(exValue, value, 15);
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
    bool ret = true; int crate = 1;
    sCfgDev *cth = &(mItem->cTh);
    sDataUnit *unit = &(mDev->line.vol);
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    if(unit->min[id] != cth->vol_min*crate) ret = false;
    if(unit->max[id] != cth->vol_max*crate) ret = false;

    return ret;
}

bool Test_ErrRange::curAlarm(int id)
{    
    bool ret = true; int crate = 1;
    sCfgDev *cth = &(mItem->cTh);
    sDataUnit *unit = &(mDev->line.cur);
    if(mDev->devType.screen == 1) crate = 10;
    if(mDev->devType.screen == 3 && mItem->ip.log  == 0 && mItem->ip.security  == 1) crate = 10;
    if((mDt->lines == 2) && id){
        if(unit->min[id]/10 != (cth->cur_min/10+1)/2) ret = false;
        if(cth->cur_max == 630){
            if( unit->max[id]/10 == (cth->cur_max/10+1)/2*crate || unit->max[id] == 315 || unit->max[id] == 3150)
                ret = true;
            else
                ret = false;
            //            if( unit->max[id]/10 != (cth->cur_max/10)/2*crate)
            //                ret = false;
        } else{
            if( unit->max[id]/10 != (cth->cur_max/10)/2*crate)
                ret = false;
        }
    } else {
        if(unit->min[id] != cth->cur_min*crate) ret = false;
        if(unit->max[id] != cth->cur_max*crate) ret = false;
    }

    return ret;
}


bool Test_ErrRange::temAlarm()
{
    bool ret = true;
    sDataUnit *unit = &(mDev->env.tem);
    if((unit->max[0] == 40) || (unit->max[0] == 60)|| (unit->max[0] == 39)) ret = true; else ret = false;
    if(unit->min[0]) ret = false;

    return ret;
}


bool Test_ErrRange::humAlarm()
{
    bool ret = true;
    sDataUnit *unit = &(mDev->env.hum);
    if(unit->max[0] != 99) ret = false;
    if(unit->min[0]) ret = false;

    return ret;
}
