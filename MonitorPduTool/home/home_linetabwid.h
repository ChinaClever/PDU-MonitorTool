#ifndef HOME_LINETABWID_H
#define HOME_LINETABWID_H

#include "comtablewid.h"

class Home_LineTabWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit Home_LineTabWid(QWidget *parent = nullptr);

signals:

protected:
    void initWid();


};

#endif // HOME_LINETABWID_H
