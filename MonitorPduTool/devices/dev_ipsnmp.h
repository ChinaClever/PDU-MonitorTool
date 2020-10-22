#ifndef DEV_IPSNMP_H
#define DEV_IPSNMP_H

#include "dev_iprtu.h"
#include "snmpclient.h"

class Dev_IpSnmp : public Dev_Object
{
    Q_OBJECT
public:
    explicit Dev_IpSnmp(QObject *parent = nullptr);

    bool readPduData();

protected:
    void run();
    int getItemByOid(const QString &oid, int id);
    bool lineNumV3();
    bool devDataV3();
    bool devDataV1();

private:
    SnmpClient *mSnmp;
};

#endif // DEV_IPSNMP_H
