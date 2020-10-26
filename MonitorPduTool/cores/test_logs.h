#ifndef TEST_LOGS_H
#define TEST_LOGS_H
#include "dbstates.h"
#include "datapacket.h"

class Test_Logs : public QThread
{
    Q_OBJECT
    explicit Test_Logs(QObject *parent = nullptr);
public:
    static Test_Logs *bulid(QObject *parent = nullptr);

    void saveLogs();
    bool updatePro(const QString &str, bool pass=true, int sec=1);

protected:
    void writeLog();
    void writeLogs();
    bool appendLogItem(const QString &str, bool pass);

private:
    sDevData *mDev;
    sCfgItem *mItem;
    sProgress *mPro;
    sDataPacket *mPacket;
    QList<sStateItem> mLogItems;
};

#endif // TEST_LOGS_H
