#ifndef TEST_CORETHREAD_H
#define TEST_CORETHREAD_H

#include "test_dataread.h"

class Test_CoreThread : public QThread
{
    Q_OBJECT
public:
    explicit Test_CoreThread(QObject *parent = nullptr);

private:
    Test_DataRead *mRead;
};

#endif // TEST_CORETHREAD_H
