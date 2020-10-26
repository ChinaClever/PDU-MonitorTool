#ifndef TEST_CORETHREAD_H
#define TEST_CORETHREAD_H

#include "test_dataread.h"
#include "test_logs.h"

class Test_CoreThread : public QThread
{
    Q_OBJECT
public:
    explicit Test_CoreThread(QObject *parent = nullptr);
    ~Test_CoreThread();


protected slots:
    void initFunSlot();

protected:
    void run();    
    void workDown();

    bool initDev();
    bool hubPort();
    void workResult();

private:
    bool isRun;
    sDevData *mDev;
    sCfgItem *mItem;
    sProgress *mPro;
    sDataPacket *mPacket;
    Test_DataRead *mRead;
    Test_Logs *mLogs;
};

#endif // TEST_CORETHREAD_H
