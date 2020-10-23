#include "test_corethread.h"

Test_CoreThread::Test_CoreThread(QObject *parent) : QThread(parent)
{
    mRead = Test_DataRead::bulid(this);
}
