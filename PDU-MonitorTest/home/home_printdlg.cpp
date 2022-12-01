#include "home_printdlg.h"
#include "ui_home_printdlg.h"

Home_PrintDlg::Home_PrintDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home_PrintDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    mItem = Cfg::bulid()->item;
    initFunSlot();
}

Home_PrintDlg::~Home_PrintDlg()
{
    delete ui;
}

void Home_PrintDlg::initFunSlot()
{
    Cfg::bulid()->initPrint();
    ui->printerCheck->setChecked(mItem->printer);
    ui->MACCheck->setChecked(mItem->macprinter);
}

void Home_PrintDlg::on_testPrintBtn_clicked()
{
    QString cmd = "DF:DF:DF:DF:DF:1F";
    bool ret = Printer_BarTender::bulid()->print(cmd);
    qDebug()<<ret <<endl;
}

void Home_PrintDlg::on_saveBtn_clicked()
{
    mItem->printer = ui->printerCheck->isChecked();
    mItem->macprinter = ui->MACCheck->isChecked();
    Cfg::bulid()->setPrinter();
    this->close();
}

void Home_PrintDlg::on_closeBtn_clicked()
{
    this->close();
}
