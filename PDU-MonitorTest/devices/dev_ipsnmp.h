#ifndef DEV_IPSNMP_H
#define DEV_IPSNMP_H

#include "dev_sirtu.h"
#include "snmpclient.h"

class Dev_IpSnmp : public QThread
{
    Q_OBJECT
    explicit Dev_IpSnmp(QObject *parent = nullptr);
public:
    static Dev_IpSnmp *bulid(QObject *parent = nullptr);
    bool readPduData();
    void resetSnmp();

protected:
    bool lineNumV3();
    bool devDataV3();
    bool devDataV1();
    int getItemByOid(const QString &oid, int id);

private:
    sDevData *mDev;
    sCfgItem *mItem;
    sProgress *mPro;    
    SnmpClient *mSnmp;
    sDataPacket *mPacket;
};

#endif // DEV_IPSNMP_H
