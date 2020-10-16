#ifndef SETUP_MAINWID_H
#define SETUP_MAINWID_H

#include <QWidget>
#include "usermainwid.h"

namespace Ui {
class Setup_MainWid;
}

class Setup_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit Setup_MainWid(QWidget *parent = nullptr);
    ~Setup_MainWid();

protected slots:
    void initFunSlot();

private:
    Ui::Setup_MainWid *ui;
    UserMainWid *mUserWid;
};

#endif // SETUP_MAINWID_H
