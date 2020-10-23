#ifndef DEV_DEFTYPE_H
#define DEV_DEFTYPE_H
#include "dev_source.h"

class Dev_TypeDef
{
    Dev_TypeDef();
public:
    static Dev_TypeDef *bulid();
    bool analysDevType(uint id);

protected:
    QString getDevStr(uint id);
    int getDevType(const QString &str);
    int getAcType(const QString &str);
    int getColMode(const QString &str);
    int getLineNum(const QString &str);
    int getSerie(const QString &str);

private:
    sDevType *mDt;
    sDataPacket *mPacket;
};

#endif // DEV_DEFTYPE_H
