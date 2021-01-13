/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "sn_serialnum.h"

Sn_SerialNum::Sn_SerialNum(QObject *parent) : Dev_Object(parent)
{
    mTypeId = Sn_DevId::bulid(this);
}

Sn_SerialNum *Sn_SerialNum::bulid(QObject *parent)
{
    Sn_SerialNum* sington = nullptr;
    if(sington == nullptr)
        sington = new Sn_SerialNum(parent);
    return sington;
}

void Sn_SerialNum::initReadCmd(sRtuItem &item)
{
    item.addr = mDev->id;
    item.fn = 0x03;
    item.reg = 0xA003;
    item.num = 4;
}

bool Sn_SerialNum::checkSn(uchar *sn, int len)
{
    bool ret = false;
    if((len == 8) && (sn[0] == 0)){
        uchar exor = mModbus->xorNum(sn, len-1);//暂时注释下面的异或和校验不对
        if(exor == sn[len-1]) {
            ret = true;
        }
    } else {
        qDebug() << "SN check err" << len << sn[0];
    }
    return ret;
}

void Sn_SerialNum::initDevType(sSnItem &it)
{
    uint id = mDev->devType.devId;
    for(int i=3; i>=0; --i) {
        it.devType[i] = (0xFF) & (id >> ((3-i)*8));
    }
    it.sn.clear();
}

bool Sn_SerialNum::analySn(uchar *sn, int len, sSnItem &it)
{
    uchar *ptr = sn;
    bool ret = checkSn(sn, len);
    if(ret) {
        for(int i=0; i<4; ++i) {
            it.date[i] = *ptr++;
        }
        it.num = (*ptr++) << 8;
        it.num += *ptr++;
        it.pc = *ptr++;
        it.exor = *ptr++;
    }

    return ret;
}

void Sn_SerialNum::toSnStr(sSnItem &it)
{
    QString cmd;
    for(int i=0; i<9; ++i) {cmd += "%" + QString::number(i+1); if(i<7)if((i%2==1)||i==6) cmd += " ";}
    QString sn  = QString(cmd)
            //.arg(it.devType[0], 2, 16, QLatin1Char('0'))
            //.arg(it.devType[1], 2, 16, QLatin1Char('0'))
            .arg(it.devType[2], 2, 16, QLatin1Char('0'))
            .arg(it.devType[3], 2, 16, QLatin1Char('0'))
            .arg(it.date[0], 2, 10, QLatin1Char('0'))
            .arg(it.date[1], 2, 10, QLatin1Char('0'))
            .arg(it.date[2], 2, 10, QLatin1Char('0'))
            .arg(it.date[3], 2, 10, QLatin1Char('0'))
            .arg(it.num, 4, 10, QLatin1Char('0'))
            .arg(it.pc, 2, 16, QLatin1Char('0'))
            .arg(it.exor, 2, 16, QLatin1Char('0'));

    it.sn = sn.toUpper();
}

bool Sn_SerialNum::readSn(sSnItem &itSn)
{
    sRtuItem itRtu;
    bool ret = false;
    uchar buf[32] = {0};
    QString str = tr("序列号读取成功");

    initReadCmd(itRtu);
    int len = mModbus->read(itRtu, buf);
    if(8 != len) len = mModbus->read(itRtu, buf);
    if(len == 8) {
        ret = analySn(buf, len, itSn); toSnStr(itSn);
        if(!ret) str = tr("序列号分析错误：%1").arg(itSn.sn);
    } else {
        str = tr("读序列号未返数据长度错误 %1").arg(len);
    }

    return mPacket->updatePro(str, ret);
}

bool Sn_SerialNum::snEnter()
{
    bool ret = mTypeId->readDevType();
    if(ret) {
        initDevType(mSnItem);
        ret = readSn(mSnItem);
        if(ret) mDev->devType.sn = mSnItem.sn;
    }

    return ret;
}

