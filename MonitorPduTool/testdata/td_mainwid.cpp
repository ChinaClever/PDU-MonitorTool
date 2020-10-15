#include "td_mainwid.h"
#include "ui_td_mainwid.h"

Td_MainWid::Td_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Td_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    mStatusTabWid = new Td_StatusTabWid(ui->groupBox);
}

Td_MainWid::~Td_MainWid()
{
    delete ui;
}
