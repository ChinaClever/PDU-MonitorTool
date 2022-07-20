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
    bool ret = true;
    if(mItem->si.led){
        mDt->ac = mItem->si.ac;
        mDt->devType = SI_PDU;
        mDt->lines = mItem->si.lines;
        mDt->dev_type = tr("SI/BM数码管");
    } else {
        ret = mSn->snEnter();
    }

    if(ret) ret = initDev();
    return ret;
}

bool Test_DevRead::readDev()
{
    bool ret = mPacket->delay(5);
    if(ret) ret = mSource->read();
    if(ret) {
        for(int i=0; i<6; ++i) {
            ret = mRtu->readPduData();
            if(ret) break; else if(!mPacket->delay(1)) break;
            if(i>1 && i%2) mRtu->changeBaudRate();
        }
    }

    return ret;
}

bool Test_DevRead::checkNet()
{
    QString ip;
    bool ret = true;
    QString str = tr("网络检测");
    for(int k=0; k<3; ++k) {
        for(int i=0; i<3; ++i) {
            ip = "192.168.1.16" + QString::number(3+i);
            ret = cm_pingNet(ip);
            if(!ret) {
                 msleep(50);
                 ip = "192.168.1.163";
                 ret = cm_pingNet(ip);
            }
            if(ret) break;
        }
        if(ret) break;
    }

    if(ret) {
        str += ip;
        mItem->ip.addr = ip;
        Cfg::bulid()->write("ip_addr", ip, "ipCfg");
    }

    if(ret) str += tr("正常");else str += tr("异常");
    return mLogs->updatePro(str, ret);
}

bool Test_DevRead::readSnmp()
{
    bool ret = true;
    if(!mItem->ip.modbus) {
        QString str = tr("SNMP通讯");
        ret = mIpSnmp->readPduData();
        if(!ret) {
            mIpSnmp->resetSnmp();
            ret = mIpSnmp->readPduData();
        }
        if(ret) str += tr("成功");
        else str += tr("失败");
        mLogs->updatePro(str, ret);
    }

    return ret;
}

bool Test_DevRead::checkIpVersion()
{
    bool ret = !isRun;
    if(ret) {
        QString str = tr("设备版本检查");
        if(mDt->version != mItem->ip.version) {
            if( mItem->ip.version ==  IP_PDUV1_HUADA){
                str += tr("正常");
            }
            else{
                str += tr("出错 期望版本V%1，实际版本V%2").arg(mItem->ip.version).arg(mDt->version);
                ret = false;
            }
        } else {
            str += tr("正常");
        }
        mLogs->updatePro(str, ret);
    }

    return ret;
}

bool Test_DevRead::checkIpLine()
{
    bool ret = !isRun;
    if(ret && mItem->ip.lines) {
        QString str = tr("设备相数检查");
        if(mDt->lines != mItem->ip.lines) {
            str += tr("出错 期望相数L=%1，实际相数L=%2").arg(mItem->ip.lines).arg(mDt->lines);
            ret = false;
        } else {
            str += tr("正常");
        }
        mLogs->updatePro(str, ret);
    }
    if(ret) ret = checkIpVersion();

    return ret;
}

bool Test_DevRead::checkSiLine()
{
    bool ret = !isRun;
    if(ret) {
        QString str = tr("设备相数检查");
        if(mDt->lines != mItem->si.lines) {
            str += tr("出错 期望相数L=%1，实际相数L=%2").arg(mItem->si.lines).arg(mDt->lines);
            ret = false;
        } else {
            str += tr("正常");
        }
        mLogs->updatePro(str, ret);
    }

    return ret;
}

bool Test_DevRead::readNet()
{
    bool ret = true;
    if(IP_PDU == mDt->devType) {
        //ret = checkNet();
        if(ret) ret = checkIpLine();
        //if(ret) ret = readSnmp();
        //if(ret) Ctrl_IpRtu::bulid(this)->start();
    } else {
        ret = checkSiLine();
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
    bool ret = true;
    mRtu->setModbus(1);
    for(int i=0; i<3; ++i) {
        ret = mRtu->readPduData();
        if(ret) break; else mRtu->changeBaudRate();
    }
    mRtu->setModbus(2);

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
