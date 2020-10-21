/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "rtu_serial.h"

Rtu_Serial::Rtu_Serial(QObject *parent) : QThread(parent)
{
    mSerial = nullptr;
}


int Rtu_Serial::readSerial(quint8 *cmd, int secs)
{
    int rtn = 0;
    if(!mSerial) return rtn;

    sProgress *pro = sDataPacket::bulid()->getPro();
    for(int i=0; i<=secs; ++i) {
        if(pro->step < Test_Over) {
            rtn = mSerial->read(cmd, 1);
            if(rtn > 0) break;
        }
    }

    return rtn;
}

bool Rtu_Serial::writeSerial(quint8 *cmd, int len)
{
    bool ret = false;
    if(mSerial) {
        ret = mSerial->isOpened();
        if(ret) {
            mSerial->write(cmd, len);
        } else {
            qDebug() << "Rtu_Serial writeSerial err !" << ret;
        }
    }

    return ret;
}

int Rtu_Serial::transmit(uchar *sent, int len, uchar *recv, int secs)
{
    int rtn = 0;
    bool ret = writeSerial(sent, len);
    if(ret) {
        rtn = readSerial(recv, secs);
    }

    return rtn;
}
