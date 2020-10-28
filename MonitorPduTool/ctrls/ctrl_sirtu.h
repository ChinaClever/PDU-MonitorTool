#ifndef CTRL_SIRTU_H
#define CTRL_SIRTU_H

#include "ctrl_iprtu.h"

class Ctrl_SiRtu : public Ctrl_Object
{
    Q_OBJECT
    explicit Ctrl_SiRtu(QObject *parent = nullptr);
public:
    static Ctrl_SiRtu *bulid(QObject *parent = nullptr);

    bool readPduData();
    bool funClearEle();
    bool setModel();

    bool setCurTh(int i);
    bool setVolTh(int i);

protected:
    bool sentRtuCmd(ushort reg, ushort value);

private:
    Dev_SiRtu *mRtu;
};

#endif // CTRL_SIRTU_H
