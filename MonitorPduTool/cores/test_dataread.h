#ifndef TEST_DATAREAD_H
#define TEST_DATAREAD_H

#include "test_logs.h"


class Test_DataRead : public Test_Object
{
    Q_OBJECT
    explicit Test_DataRead(QObject *parent = nullptr);
public:
    static Test_DataRead *bulid(QObject *parent = nullptr);

    bool readSn();
    bool readDev();
    bool readNet();

protected:
    void run();
    bool readPdu();
    bool checkNet();
    bool readSnmp();

protected slots:
    void initFunSlot();

private:
    Dev_SiRtu *mSiRtu;
    Dev_IpRtu *mIpRtu;
    Dev_SerialNum *mSn;
    Dev_IpSnmp *mIpSnmp;
    Dev_Source *mSource;
    Test_Logs *mLogs;
};

#endif // TEST_DATAREAD_H
