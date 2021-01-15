/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "home_setdlg.h"
#include "ui_home_setdlg.h"

Home_SetDlg::Home_SetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home_SetDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    mItem = Cfg::bulid()->item;
    QTimer::singleShot(500,this,SLOT(initFunSlot()));
}

Home_SetDlg::~Home_SetDlg()
{
    delete ui;
}

void Home_SetDlg::initFunSlot()
{
    initCntLab();
    initThresholdWid();
    int v = mItem->ip.version-1?1:0;
    ui->ipTypeBox->setCurrentIndex(v);
    ui->userEdit->setText(mItem->user);
    ui->languageBox->setCurrentIndex(mItem->ip.language);
    ui->lineBox->setCurrentIndex(mItem->ip.lines);
    ui->ipModeBox->setCurrentIndex(mItem->ip.modbus);
    ui->sBox->setCurrentIndex(mItem->ip.standard);
    ui->logBox->setCurrentIndex(mItem->ip.log);
    on_ipTypeBox_currentIndexChanged(v);
}


void Home_SetDlg::initThresholdWid()
{
    sCfgDev *cth = &(mItem->cTh);
    ui->comboBox->setCurrentIndex(cth->type);
    on_comboBox_currentIndexChanged(cth->type);
    ui->modifyCheck->setChecked(cth->enModify);
}

bool Home_SetDlg::getThresholdWid()
{
    sCfgDev *cth = &(mItem->cTh);
    cth->type = ui->comboBox->currentIndex();
    cth->vol_min = ui->volMinSpin->value();
    cth->vol_max = ui->volMaxSpin->value();
    cth->cur_min = ui->curMinSpin->value()*10;
    cth->cur_max = ui->curMaxSpin->value()*10;

    mItem->user = ui->userEdit->text();
    mItem->cnt.num = ui->numSpin->value();
    cth->enModify = ui->modifyCheck->isChecked()?1:0;

    mItem->si.led = ui->ledCheck->isChecked();
    int rtn = ui->siLineBox->currentIndex();
    if(rtn) {
        mItem->si.ac = AC;
        mItem->si.lines = rtn;
    } else {
        mItem->si.ac = DC;
        mItem->si.lines = 1;
    }

    mItem->ip.version = ui->ipTypeBox->currentIndex()?3:1;
    mItem->ip.language = ui->languageBox->currentIndex();
    mItem->ip.lines = ui->lineBox->currentIndex();
    mItem->ip.modbus = ui->ipModeBox->currentIndex();
    mItem->ip.standard = ui->sBox->currentIndex();
    mItem->ip.log = ui->logBox->currentIndex();

    return true;
}


void Home_SetDlg::setThresholdWid()
{
    sCfgDev *cth = &(mItem->cTh);
    ui->volMinSpin->setValue(cth->vol_min);
    ui->volMaxSpin->setValue(cth->vol_max);
    ui->curMinSpin->setValue(cth->cur_min/10.0);
    ui->curMaxSpin->setValue(cth->cur_max/10.0);
}

void Home_SetDlg::on_comboBox_currentIndexChanged(int index)
{
    bool en = true;
    sCfgDev *cth = &(mItem->cTh);
    cth->type = index;
    if(index) {
        cth->vol_min = 80;
        cth->vol_max = 276;
        cth->cur_min = 0;
        switch (index) {
        case 1:  cth->cur_max = 320; break;
        case 2:  cth->cur_max = 160; break;
        case 3:  cth->cur_max = 630; break;
        }
    } else {
        en = false;
    }

    setThresholdWid();
    ui->volMinSpin->setEnabled(en);
    ui->volMaxSpin->setEnabled(en);
    ui->curMinSpin->setEnabled(en);
    ui->curMaxSpin->setEnabled(en);
}

void Home_SetDlg::on_okBtn_clicked()
{
    bool ret = getThresholdWid();
    if(ret) {
        this->close();
        Cfg::bulid()->writeCfgDev();
    }
}

void Home_SetDlg::initCntLab()
{
    ui->numSpin->setValue(mItem->cnt.num);
    QString str = tr("设备数量：%1 成功：%2 失败：%3 ")
            .arg(mItem->cnt.all).arg(mItem->cnt.ok).arg(mItem->cnt.err);
    ui->cntLab->setText(str);
}

void Home_SetDlg::on_resBtn_clicked()
{
    bool ret = MsgBox::question(this, tr("请确认，重新计数？"));
    if(ret) {
        mItem->cnt.all = 0;
        mItem->cnt.ok = 0;
        mItem->cnt.err = 0;

        initCntLab();
        Cfg::bulid()->writeCnt();
    }
}

void Home_SetDlg::on_ipTypeBox_currentIndexChanged(int index)
{
    bool res = true;
    if(index)  res = false;

    ui->sBox->setHidden(res);
    ui->logBox->setHidden(res);
    ui->label_8->setHidden(res);
    ui->label_11->setHidden(res);
}
