#include "test_corethread.h"

Test_CoreThread::Test_CoreThread(QObject *parent) : QThread(parent)
{
    QTimer::singleShot(500,this,SLOT(initFunSlot()));
}

Test_CoreThread::~Test_CoreThread()
{
    isRun = false;
    wait();
}

void Test_CoreThread::initFunSlot()
{
    isRun = false;
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();
    mDev = mPacket->getDev();
    mLogs = Test_Logs::bulid(this);
    mRead = Test_DataRead::bulid(this);
}


bool Test_CoreThread::hubPort()
{
    bool ret = false;
    QByteArray array;
    QString str = tr("设备级联口连接");
    SerialPort *ser = mItem->coms.ser2;
    int rtn = ser->read(array);
    if(rtn > 20) {
        str += tr("正常");
        ret = true;
    } else {
        str += tr("错误");
    }

    return mLogs->updatePro(str, ret);
}


bool Test_CoreThread::initDev()
{
    bool ret  = mRead->readSn();
    if(ret) {
        mItem->coms.ser2->reflush();
        QString str = tr("设备数据读取");
        ret = mRead->readDev();
        if(ret) str += tr("成功");
        else str += tr("失败");
        mLogs->updatePro(str, ret, 2);
    }
    if(ret) mRead->readNet();

    return hubPort();
}


void Test_CoreThread::workResult()
{
    mLogs->saveLogs();
    mPro->step = Test_Over;
}






void Test_CoreThread::workDown()
{
    mPro->step = Test_Start;
    bool ret = initDev();
    if(ret) {


    }

    workResult();
}


void Test_CoreThread::run()
{
    if(isRun) return;
    isRun = true;

    workDown();
    isRun = false;
}
