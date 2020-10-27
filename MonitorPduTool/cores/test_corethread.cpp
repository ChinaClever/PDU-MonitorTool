/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_corethread.h"

Test_CoreThread::Test_CoreThread(QObject *parent) : Test_Object(parent)
{

}


void Test_CoreThread::initFunSlot()
{
    mLogs = Test_Logs::bulid(this);
    mErr = Test_ErrRange::bulid(this);
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
        mLogs->updatePro(str, ret);
    }
    if(ret) ret = hubPort();
    if(ret) ret = mRead->readNet();

    return ret;
}

bool Test_CoreThread::volErrRange(int i)
{
    QString str = tr("电压 L%1 ").arg(i+1);
    bool ret = mErr->volErr(i);
    if(!ret) {
        mRead->readDev();
        ret = mErr->volErr(i);
    }

    if(ret)  str += tr("正常");
    else str += tr("错误，电压=%1V").arg(mDev->line.vol.value[i]);

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::curErrRange(int i)
{
    QString str = tr("电流 L%1 ").arg(i+1);
    bool ret = mErr->curErr(i);
    if(!ret) {
        mRead->readDev();
        ret = mErr->curErr(i);
    }

    if(ret)  str += tr("正常");
    else str += tr("错误，电流=%1A").arg(mDev->line.cur.value[i]/COM_RATE_CUR);

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::powErrRange(int i)
{
    QString str = tr("功率 L%1 ").arg(i+1);
    bool ret = mErr->powErr(i);
    if(!ret) {
        mRead->readDev();
        ret = mErr->powErr(i);
    }

    if(ret)  str += tr("正常");
    else str += tr("错误，功率=%1Kw").arg(mDev->line.pow[i]/COM_RATE_POW);

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::envErrRange()
{
    QString str = tr("传感器温度");
    bool ret = mErr->temErr();
    if(ret)  str += tr("正常");
    else str += tr("错误，温度=%1").arg(mDev->env.tem.value[0]);

    ret = mLogs->updatePro(str, ret);
    if(ret) {
        str = tr("传感器湿度");
        ret = mErr->humErr();
        if(ret)  str += tr("正常");
        else str += tr("错误，湿度=%1").arg(mDev->env.hum.value[0]);
        ret = mLogs->updatePro(str, ret);
    }

    return ret;
}

bool Test_CoreThread::checkErrRange()
{
    bool ret = mRead->readDev();
    if(ret) {
        for(int i=0; i<mDev->line.size; ++i) {
            ret = volErrRange(i); if(!ret) break;
            ret = curErrRange(i); if(!ret) break;
            ret = powErrRange(i); if(!ret) break;
        }
        ret = envErrRange();
    }

    return ret;
}

bool Test_CoreThread::volAlarmErr(int i)
{
    QString str = tr("电压报警阈值 L%1 ").arg(i+1);
    bool ret = mErr->volAlarm(i);
    if(ret)  str += tr("正常");
    else str += tr("错误");

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::curAlarmErr(int i)
{
    QString str = tr("电流报警阈值 L%1 ").arg(i+1);
    bool ret = mErr->curAlarm(i);
    if(ret) str += tr("正常");
    else str += tr("错误");

    return mLogs->updatePro(str, ret);
}

bool Test_CoreThread::checkAlarmErr()
{
    bool ret = true;
    sCfgTh *cth = &(mItem->cTh);
    if(cth->type) {
        for(int i=0; i<mDev->line.size; ++i) {
            ret = volAlarmErr(i); if(!ret) break;
            ret = curAlarmErr(i); if(!ret) break;
        }
    }

    return ret;
}


void Test_CoreThread::workResult(bool res)
{
    mLogs->saveLogs();
    mLogs->updatePro(tr("测试结束"), res);
    mPro->step = Test_Over;
}


void Test_CoreThread::workDown()
{
    mPro->step = Test_Start;
    bool ret = initDev();
    if(ret) {
        ret = checkErrRange();
        if(ret) ret = checkAlarmErr();
    }

    workResult(ret);
}


void Test_CoreThread::run()
{
    if(isRun) return;
    isRun = true;

    workDown();
    isRun = false;
}
