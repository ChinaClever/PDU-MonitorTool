#ifndef TEST_ERRRANGE_H
#define TEST_ERRRANGE_H

#include "test_devread.h"

class Test_ErrRange : public Test_Object
{
    Q_OBJECT
    explicit Test_ErrRange(QObject *parent = nullptr);
public:
    static Test_ErrRange *bulid(QObject *parent = nullptr);

    bool volErr(int id);
    bool curErr(int id);
    bool powErr(int id);

    bool temErr();
    bool humErr();

    bool volAlarm(int id);
    bool curAlarm(int id);

protected:
    bool checkErrRange(int exValue, int value, int err);

protected slots:
    void initFunSlot();

private:
    sDevData *mSourceDev;
};

#endif // TEST_ERRRANGE_H
