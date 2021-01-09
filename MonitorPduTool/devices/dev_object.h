#ifndef DEV_OBJECT_H
#define DEV_OBJECT_H

#include "rtu_modbus.h"

class Dev_Object : public QThread
{
    Q_OBJECT
public:
    explicit Dev_Object(QObject *parent = nullptr);

    virtual bool readPduData()=0;
    void setModbus(int id);
    void changeBaudRate() {mModbus->changeBaudRate();}

protected:
    uchar *toInt(uchar *ptr, int line, uint *value);
    uchar *toChar(uchar *ptr, int line, uchar *value);
    uchar *toShort(uchar *ptr, int line, ushort *value);

    ushort getShort(uchar *ptr);
    uchar *getShort(uchar *ptr, int line, uchar *value);
    uchar *toOutputEle(uchar *ptr, int line, uint *value);
    uchar *toThreshold(uchar *ptr, int line, sDataUnit &unit);
    uchar *toEnvTh(uchar *ptr, sDataUnit &unit);

protected slots:
    virtual void initFunSlot();

protected:
    sDevType *mDt;
    sDevData *mDev;
    RtuRw *mModbus;
    sCfgItem *mItem;
    sProgress *mPro;
    sDataPacket *mPacket;
};

#endif // DEV_OBJECT_H
