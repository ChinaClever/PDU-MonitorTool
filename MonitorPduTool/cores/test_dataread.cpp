#include "test_dataread.h"

Test_DataRead::Test_DataRead(QObject *parent) : QThread(parent)
{
    isRun = false;
    mSiRtu = new Dev_SiRtu(this);
    mIpRtu = new Dev_IpRtu(this);
    mSn = Dev_SerialNum::bulid(this);
    mIpSnmp = Dev_IpSnmp::bulid(this);
    mSource = Dev_Source::bulid(this);
    sDevData *dev = sDataPacket::bulid()->getDev();
    mDt = &(dev->devType);
}

Test_DataRead::~Test_DataRead()
{
    isRun = false;
    wait();
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
    bool ret = mSn->snEnter();
    if(ret) {
        if(IP_PDU == mDt->devType) {
            mIpSnmp->start();
        }
    }

    return ret;
}

bool Test_DataRead::readDev()
{
    bool ret = mSource->read();
    if(ret) ret = readPdu();
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

    sDataPacket::bulid()->init();
    sProgress *pro = sDataPacket::bulid()->getPro();
    pro->step = Collect_Start;

    /////=======
//    bool ret = true;
    mDt->devType = IP_PDU;

    bool ret  = readSn();
    if(ret) readPdu();
    pro->step = Test_End;

    isRun = false;
}
