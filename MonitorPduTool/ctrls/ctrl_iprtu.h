#ifndef CTRL_IPRTU_H
#define CTRL_IPRTU_H

#include "ctrl_object.h"

class Ctrl_IpRtu : public Ctrl_Object
{
    Q_OBJECT
    explicit Ctrl_IpRtu(QObject *parent = nullptr);
public:
    static Ctrl_IpRtu *bulid(QObject *parent = nullptr);

    bool readPduData();
    bool setCurTh(int i);
    bool setVolTh(int i);

protected:
    bool sentRtuCmd(ushort reg, ushort value);

private:
    Dev_IpRtu *mRtu;
};

#endif // CTRL_IPRTU_H
