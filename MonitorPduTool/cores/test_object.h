#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "dev_serialnum.h"

class Test_Object : public QThread
{
    Q_OBJECT
public:
    explicit Test_Object(QObject *parent = nullptr);
    ~Test_Object();

protected slots:
    virtual void initFunSlot(){}

protected:
    bool isRun;
    sDevType *mDt;
    sDevData *mDev;
    sCfgItem *mItem;
    sProgress *mPro;
    sDataPacket *mPacket;
};

#endif // TEST_OBJECT_H
