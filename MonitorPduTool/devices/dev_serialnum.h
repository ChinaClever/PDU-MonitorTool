#ifndef DEV_SERIALNUM_H
#define DEV_SERIALNUM_H

#include "dev_typeid.h"

struct sSnItem
{
    sSnItem() {}
    char devType[4];
    uchar date[4];
    ushort num;
    uchar pc;
    uchar exor;
    QString sn;
};


class Dev_SerialNum : public QThread
{
    Q_OBJECT
    explicit Dev_SerialNum(QObject *parent = nullptr);
public:
    static Dev_SerialNum *bulid(QObject *parent = nullptr);

    bool snEnter();

protected:
    void toSnStr(sSnItem &it);
    bool analySn(uchar *sn, int len, sSnItem &it);
    bool checkSn(uchar *sn, int len);
    void initReadCmd(sRtuItem &item);
    void initDevType(sSnItem &it);

    bool readSn(sSnItem &itSn);

private:
    sSnItem mSnItem;
    sDevData *mDev;
    RtuRw *mModbus;
    sCfgItem *mItem;
    sProgress *mPro;
    sDataPacket *mPacket;
    Dev_TypeId *mTypeId;
};

#endif // DEV_SERIALNUM_H
