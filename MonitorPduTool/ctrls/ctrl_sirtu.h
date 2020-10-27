#ifndef CTRL_SIRTU_H
#define CTRL_SIRTU_H

#include "dev_serialnum.h"

class Ctrl_SiRtu : public Dev_Object
{
    Q_OBJECT
public:
    explicit Ctrl_SiRtu(QObject *parent = nullptr);

    bool readPduData();
    bool funClearEle();
    bool setModel();


protected:
    bool sentRtuCmd(ushort reg, ushort value);

private:
};

#endif // CTRL_SIRTU_H
