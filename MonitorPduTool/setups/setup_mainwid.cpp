#include "setup_mainwid.h"
#include "ui_setup_mainwid.h"

Setup_MainWid::Setup_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setup_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(rand()%13,this,SLOT(initFunSlot()));
}

Setup_MainWid::~Setup_MainWid()
{
    delete ui;
}

void Setup_MainWid::initFunSlot()
{
    mUserWid = new UserMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mUserWid);
}
