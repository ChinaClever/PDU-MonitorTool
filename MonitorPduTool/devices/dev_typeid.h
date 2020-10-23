#ifndef DEV_TYPEID_H
#define DEV_TYPEID_H
#include "dev_typedef.h"

class Dev_TypeId: public QThread
{
    Q_OBJECT
    explicit Dev_TypeId(QObject *parent = nullptr);
public:
    static Dev_TypeId *bulid(QObject *parent = nullptr);

    bool readDevType();
protected:
    bool readDevId();
    void initReadType(sRtuItem &it);
    bool analysDevType(uchar *buf, int len);

private:
    sDevData *mDev;
    RtuRw *mModbus;
    sCfgItem *mItem;
    sProgress *mPro;
    sDataPacket *mPacket;
    Dev_TypeDef *mTypeDef;
};

#endif // DEV_TYPEID_H
