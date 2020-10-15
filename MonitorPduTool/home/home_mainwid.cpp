/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "home_mainwid.h"
#include "ui_home_mainwid.h"

Home_MainWid::Home_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);

    initWid();

    //    mTableWid = new Home_DataTabWid(ui->tableWid);
    //    connect(mModeWid, SIGNAL(startSig()), this, SIGNAL(startSig()));
}

Home_MainWid::~Home_MainWid()
{
    delete ui;
}




void Home_MainWid::initWid()
{
    mWorkWid = new Home_WorkWid(ui->workWid);

    mLineTabWid = new Home_LineTabWid(ui->tabWidget);
    ui->tabWidget->insertTab(0, mLineTabWid, tr("相监测数据列表"));

    mThTabWid = new Home_ThresholdTabWid(ui->tabWidget);
    ui->tabWidget->insertTab(1, mThTabWid, tr("报警阈值信息"));

    mEnvTabWid = new Home_EnvTabWid(ui->tabWidget);
    ui->tabWidget->insertTab(2, mEnvTabWid, tr("传感器环境状态"));
}
