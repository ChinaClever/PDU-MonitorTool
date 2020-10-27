/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_dataread.h"

Test_DataRead::Test_DataRead(QObject *parent) : Test_Object(parent)
{

}

void Test_DataRead::initFunSlot()
{
    mSiRtu = new Dev_SiRtu(this);
    mIpRtu = new Dev_IpRtu(this);
    mLogs = Test_Logs::bulid(this);
    mSn = Dev_SerialNum::bulid(this);
    mIpSnmp = Dev_IpSnmp::bulid(this);
    mSource = Dev_Source::bulid(this);
}

Test_DataRead *Test_DataRead::bulid(QObject *parent)
{
    static Test_DataRead* sington = nullptr;
    if(sington == nullptr)
        sington = new Test_DataRead(parent);
    return sington;
}

bool Test_DataRead::readSn()
{
    return mSn->snEnter();
}

bool Test_DataRead::readDev()
{
    bool ret = mSource->read();
    if(ret) ret = readPdu();
    return ret;
}

bool Test_DataRead::checkNet()
{
    QString str = tr("网络测试失败");
    bool ret = cm_checkIp("192.168.1.163");
    if(ret) {
        str = tr("网络测试成功");
    }

    return mLogs->updatePro(str, ret);
}

bool Test_DataRead::readSnmp()
{
    bool ret = true;
    QString str = tr("SNMP通讯");
    ret = mIpSnmp->readPduData();
    if(ret) str += tr("成功");
    else str += tr("失败");

    return mLogs->updatePro(str, ret);
}


bool Test_DataRead::readNet()
{
    bool ret = true;
    if(IP_PDU == mDt->devType) {
        ret = checkNet();
        if(ret)  ret = readSnmp();
    }

    return ret;
}

bool Test_DataRead::readPdu()
{
    bool ret = false;
    Dev_Object *dev = nullptr;
    switch (mDt->devType) {
    case SI_PDU:  dev = mSiRtu; break;
    case IP_PDU:  dev = mIpRtu; break;
    }
    if(dev) ret = dev->readPduData();

    return ret;
}


void Test_DataRead::run()
{
    if(isRun) return;
    isRun = true;

    mPacket->init();
    mPro->step = Collect_Start;

    bool ret  = readSn();
    if(ret) {
        QString str = tr("设备数据读取");
        ret = readPdu();
        if(ret) str += tr("成功");
        else str += tr("失败");
        mPacket->updatePro(str, ret);
    }
    mPacket->updatePro(tr("已结束"), ret);
    mPro->step = Test_End;

    isRun = false;
}
