/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_typedef.h"
#include "common/json/json_build.h"
#include "common/json/json_recv.h"

Dev_TypeDef::Dev_TypeDef()
{
    sDevData *dev = sDataPacket::bulid()->getDev();
    mDt = &(dev->devType);

    QJsonObject json;
    Json_Build::bulid()->getJson(json);
    Json_Recv::bulid()->recv("PDU-CalibrateTool");
}

Dev_TypeDef * Dev_TypeDef::bulid()
{
    static  Dev_TypeDef* sington = nullptr;
    if(sington == nullptr)
        sington = new  Dev_TypeDef();
    return sington;
}

QString Dev_TypeDef::getDevStr(uint id)
{
    mDt->dev_type = Json_Recv::bulid()->getDevTypeByID(id);
    return mDt->dev_type;
}

int Dev_TypeDef::getDevType(const QString &str)
{
    int ret = 0;
    if(str.contains("ZPDU")) ret = ZPDU;
    if(str.contains("MPDU")) ret = MPDU;
    if(str.contains("RPDU")) ret = RPDU;

    if(str.contains("BM-PDU")) ret = BM_PDU;
    if(str.contains("SI-PDU")) ret = SI_PDU;
    if(str.contains("IP-PDU")) {
        ret = IP_PDU;
        if(str.contains("SNMPV3")) mDt->version = 3;
    }

    return ret;
}

int Dev_TypeDef::getAcType(const QString &str)
{
    int ret = AC;
    if(str.contains("直流")) ret = DC;

    return ret;
}

int Dev_TypeDef::getColMode(const QString &str)
{
    int ret = Transformer;
    if(str.contains("锰铜")) ret = Mn;
    if(mDt->devType > RPDU) ret = Transformer;

    return ret;
}

int Dev_TypeDef::getLineNum(const QString &str)
{
    int ret = 1;
    if(str.contains("三相")) ret = 3;

    return ret;
}

int Dev_TypeDef::getSerie(const QString &str)
{
    int ret = 0;
    if(str.contains("A系列")) ret = 1;
    if(str.contains("B系列")) ret = 2;
    if(str.contains("C系列")) ret = 3;
    if(str.contains("B/D系列")) ret = 4;

    return ret;
}

bool Dev_TypeDef::analysDevType(uint id)
{
    bool ret = true;
    QString str = getDevStr(id);
    if(str.size()) {
        mDt->devId = id;
        mDt->devType = getDevType(str);
        mDt->ac = getAcType(str);
        mDt->specs = getColMode(str);
        mDt->series = getSerie(str);
        mDt->lines = getLineNum(str);
    } else {
        ret = false;
    }

    return ret;
}

