#ifndef HOME_SETDLG_H
#define HOME_SETDLG_H

#include <QDialog>
#include "common.h"

namespace Ui {
class Home_SetDlg;
}

class Home_SetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit Home_SetDlg(QWidget *parent = nullptr);
    ~Home_SetDlg();

private:
    Ui::Home_SetDlg *ui;
};

#endif // HOME_SETDLG_H
