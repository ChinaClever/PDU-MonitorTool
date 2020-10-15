#ifndef HOME_WORKWID_H
#define HOME_WORKWID_H

#include <QWidget>
#include "home_setdlg.h"

namespace Ui {
class Home_WorkWid;
}

class Home_WorkWid : public QWidget
{
    Q_OBJECT

public:
    explicit Home_WorkWid(QWidget *parent = nullptr);
    ~Home_WorkWid();

protected:
    void initLayout();
    void setInsertTextColor(const QColor &color);

private slots:
    void on_setBtn_clicked();

private:
    Ui::Home_WorkWid *ui;

    Home_SetDlg *mSetDlg;
};

#endif // HOME_WORKWID_H
