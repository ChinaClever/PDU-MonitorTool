#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "navbarwid.h"
#include "td_mainwid.h"

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

    Td_MainWid *mTdWid;
    NavBarWid *mNavBarWid;
    Home_MainWid *mHomeWid;
};
#endif // MAINWINDOW_H
