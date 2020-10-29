/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_devread.h"

Test_DevRead::Test_DevRead(QObject *parent) : Test_Object(parent)
{

}

void Test_DevRead::initFunSlot()
{
    mRtu = nullptr;
    mSiRtu = Dev_SiRtu::bulid(this);
    mIpRtu = Dev_IpRtu::bulid(this);
    mLogs = Test_Logs::bulid(this);
    mSn = Sn_SerialNum::bulid(this);
    mIpSnmp = Dev_IpSnmp::bulid(this);
    mSource = Dev_Source::bulid(this);
}

Test_DevRead *Test_DevRead::bulid(QObject *parent)
{
    static Test_DevRead* sington = nullptr;
    if(sington == nullptr)
        sington = new Test_DevRead(parent);
    return sington;
}

bool Test_DevRead::readSn()
{
    bool ret = mSn->snEnter();
    if(ret) ret = initDev();
    return ret;
}

bool Test_DevRead::readDev()
{
    bool ret = mSource->read();
    if(ret) ret = mRtu->readPduData();
    return ret;
}

bool Test_DevRead::checkNet()
{
    QString str = tr("网络测试失败");
    bool ret = cm_checkIp(mItem->cTh.ip_addr);
    if(ret) {
        str = tr("网络测试成功");
    }

    return mLogs->updatePro(str, ret);
}

bool Test_DevRead::readSnmp()
{
    bool ret = true;
    QString str = tr("SNMP通讯");
    ret = mIpSnmp->readPduData();
    if(ret) str += tr("成功");
    else str += tr("失败");

    return mLogs->updatePro(str, ret);
}

bool Test_DevRead::readNet()
{
    bool ret = true;
    if(IP_PDU == mDt->devType) {
        ret = checkNet();
        if(ret)  ret = readSnmp();
    }

    return ret;
}

bool Test_DevRead::initDev()
{
    bool ret = true;
    switch (mDt->devType) {
    case SI_PDU:  mRtu = mSiRtu; break;
    case IP_PDU:  mRtu = mIpRtu; break;
    default: ret = false; break;
    }

    return ret;
}

bool Test_DevRead::readHub()
{
    mRtu->setModbus(2);
    bool ret = mRtu->readPduData();
    if(ret) mRtu->setModbus(1);

    return ret;
}



void Test_DevRead::run()
{
    if(isRun) return;
    isRun = true;

    mPacket->init();
    mPro->step = Collect_Start;

    bool ret  = readSn();
    if(ret) {
        QString str = tr("设备数据读取");
        ret = mRtu->readPduData();
        if(ret) str += tr("成功");
        else str += tr("失败");
        mPacket->updatePro(str, ret);
    }
    mPacket->updatePro(tr("已结束"), ret);
    mPro->step = Test_End;

    isRun = false;
}
