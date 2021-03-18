#ifndef DEV_IPTHREAD_H
#define DEV_IPTHREAD_H

#include "dev_ipsnmp.h"

class Dev_IpRtu : public Dev_Object
{
    Q_OBJECT
protected:
    explicit Dev_IpRtu(QObject *parent = nullptr);
public:
    static Dev_IpRtu *bulid(QObject *parent = nullptr);
    bool readPduData();

protected:
    int recvLine(int len);
    void initRtuItem(sRtuItem &it);
    bool recvPacket(uchar *buf, int len);

    int recvDataV1(uchar *ptr);
    int recvDataV3(uchar *ptr);
    uchar *getSwitch(uchar *ptr, int line, uchar *value);

};

#endif // DEV_IPTHREAD_H
