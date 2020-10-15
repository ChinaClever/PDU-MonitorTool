#ifndef TD_STATUSTABWID_H
#define TD_STATUSTABWID_H

#include "comtablewid.h"

class Td_StatusTabWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit Td_StatusTabWid(QWidget *parent = nullptr);

signals:

protected:
    void initWid();

};

#endif // TD_STATUSTABWID_H
