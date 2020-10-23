#ifndef TEST_DATAREAD_H
#define TEST_DATAREAD_H

#include "dev_serialnum.h"

class Test_DataRead : public QThread
{
    Q_OBJECT
    explicit Test_DataRead(QObject *parent = nullptr);
public:
    static Test_DataRead *bulid(QObject *parent = nullptr);
    ~Test_DataRead();

    bool readSn();
    bool readDev();

protected:
    void run();
    bool readPdu();

private:
    bool isRun;
    sDevType *mDt;
    Dev_SiRtu *mSiRtu;
    Dev_IpRtu *mIpRtu;
    Dev_SerialNum *mSn;
    Dev_IpSnmp *mIpSnmp;
    Dev_Source *mSource;
};

#endif // TEST_DATAREAD_H
