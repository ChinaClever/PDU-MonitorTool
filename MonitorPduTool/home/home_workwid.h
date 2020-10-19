#ifndef HOME_WORKWID_H
#define HOME_WORKWID_H

#include <QWidget>
#include "home_manualdlg.h"

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
    void timeoutDone();
    void on_setBtn_clicked();
    void on_startBtn_clicked();

private:
    Ui::Home_WorkWid *ui;

    QTimer *timer;
    Home_SetDlg *mSetDlg;
    Home_ManualDlg *mManualDlg;
};

#endif // HOME_WORKWID_H
