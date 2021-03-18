#ifndef DEV_SITHREAD_H
#define DEV_SITHREAD_H

#include "dev_object.h"

class Dev_SiRtu : public Dev_Object
{
    Q_OBJECT
protected:
    explicit Dev_SiRtu(QObject *parent = nullptr);
public:
    static Dev_SiRtu *bulid(QObject *parent = nullptr);
    bool readPduData();

protected:
    int recvLine(int len);
    void initRtuItem(sRtuItem &it);
    bool recvPacket(uchar *buf, int len);
    int recvAcData(uchar *ptr, int line);
    int recvDcData(uchar *ptr, int line);
};

#endif // DEV_SITHREAD_H
