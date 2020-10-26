/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_ipsnmp.h"

Dev_IpSnmp::Dev_IpSnmp(QObject *parent) : QThread(parent)
{
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();
    mDev = mPacket->getDev();
    mSnmp = SnmpClient::bulid(this);
}

Dev_IpSnmp *Dev_IpSnmp::bulid(QObject *parent)
{
    static Dev_IpSnmp* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_IpSnmp(parent);
    return sington;
}

int Dev_IpSnmp::getItemByOid(const QString &oid, int id)
{
    QString res = QString(oid).remove(IP_MIB_OID).simplified();
    QStringList list = res.split(".");
    return list.at(id).toInt();
}

bool Dev_IpSnmp::lineNumV3()
{
    bool ret = true;
    QString oid(MIB_OID_CLEVER); oid += "10.3.1.4";
    QtSnmpDataList values = mSnmp->requestValue(oid);
    if(values.size()) {
        QtSnmpData value = values.first();
        sObjData *obj = &(mDev->line);
        obj->size = value.data().toHex().toInt(&ret,16);
        obj->vol.size = obj->cur.size = obj->size;
    } else {
        ret = false;
    }

    return ret;
}

bool Dev_IpSnmp::devDataV3()
{
    bool ret = lineNumV3(); if(!ret) return ret;
    QtSnmpDataList values = mSnmp->requestValue(IP_MIB_OID);
    for(const auto& value : values) {
        sObjData *obj = &(mDev->line);
        int res = value.data().toHex().toInt(&ret,16);
        int id = getItemByOid(value.address(), 1);
        switch (id) {
        case 1: obj->vol.value[0] = res; break;
        case 2: obj->vol.value[1] = res; break;
        case 3: obj->vol.value[2] = res; break;

        case 4: obj->cur.value[0] = res; break;
        case 5: obj->cur.value[1] = res; break;
        case 6: obj->cur.value[2] = res; break;

        case 7: obj->pf[0] = res; break;
        case 8: obj->pf[1] = res; break;
        case 9: obj->pf[2] = res; break;

        case 10: obj->pow[0] = res; break;
        case 11: obj->pow[1] = res; break;
        case 12: obj->pow[2] = res; break;

        case 13: obj->aPow[0] = res; break;
        case 14: obj->aPow[1] = res; break;
        case 15: obj->aPow[2] = res; break;

        case 16: obj->ele[0] = res; break;
        case 17: obj->ele[1] = res; break;
        case 18: obj->ele[2] = res; break;

        case 19: obj->sw[0] = res==2?1:0; break;
        case 20: obj->sw[1] = res==2?1:0; break;
        case 21: obj->sw[2] = res==2?1:0; break;

        case 22: mDev->hz = res; break;
        case 23: mDev->env.tem.value[0] = res; break;
        case 24: mDev->env.hum.value[0] = res; break;
        default:         break;
        }
    }

    return values.size();
}

bool Dev_IpSnmp::devDataV1()
{
    bool ret; QStringList oids;
    for(int k=1; k<12; k++)  oids << IP_MIB_OID + QString(".%1").arg(k);
    QtSnmpDataList values = mSnmp->requestValue(oids);

    for(const auto& value : values) {
        sObjData *obj = &(mDev->line);
        // obj->vol.size = obj->cur.size = obj->size = 3;

        int res = value.data().toHex().toInt(&ret,16);
        int id = getItemByOid(value.address(), 1);
        switch (id%12) {
        case 1: obj->vol.value[0] = res; break;
        case 2: obj->vol.value[1] = res; break;
        case 3: obj->vol.value[2] = res; break;

        case 4: obj->cur.value[0] = res; break;
        case 5: obj->cur.value[1] = res; break;
        case 6: obj->cur.value[2] = res; break;

        case 7: obj->ele[0] = res; break;
        case 8: obj->ele[1] = res; break;
        case 9: obj->ele[2] = res; break;

        case 10: mDev->env.tem.value[0] = res; break;
        case 11: mDev->env.hum.value[0] = res; break;
        default:         break;
        }
    }

    return values.size();
}

bool Dev_IpSnmp::readPduData()
{
    bool ret = true;
    if(mDev->devType.version == 3) {
        ret = devDataV3();
    } else {
        ret = devDataV1();
    }

    return ret;
}

