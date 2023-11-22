#ifndef JSONPACK_H
#define JSONPACK_H
#include "datapacket.h"


class Json_Pack
{
    Json_Pack();
public:
    static Json_Pack *bulid();
    void getJson(QJsonObject &json, QByteArray &ba);
protected:
    void head(QJsonObject &obj);
    void pduInfo(QJsonObject &json);
    int objData(QJsonObject &obj);
    sProgress *mPro;
};

#endif // JSONPACK_H
