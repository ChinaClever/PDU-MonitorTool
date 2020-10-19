#include "home_manualdlg.h"
#include "ui_home_manualdlg.h"

Home_ManualDlg::Home_ManualDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home_ManualDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
}

Home_ManualDlg::~Home_ManualDlg()
{
    delete ui;
}
