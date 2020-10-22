#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "navbarwid.h"
#include "td_mainwid.h"
#include "logmainwid.h"
#include "setup_mainwid.h"
#include "dev_ipsnmp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void initWid();

protected slots:
    void initFunSlot();
    void navBarSlot(int);

private:
    Ui::MainWindow *ui;

    Dev_IpSnmp *mSnmp;

    LogMainWid *mLog;
    Td_MainWid *mTdWid;
    NavBarWid *mNavBarWid;
    Home_MainWid *mHomeWid;
    Setup_MainWid *mSetupWid;
};
#endif // MAINWINDOW_H
