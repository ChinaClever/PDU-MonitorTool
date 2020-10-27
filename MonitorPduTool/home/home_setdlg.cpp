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
    ui->userEdit->setText(mItem->user);
}


void Home_SetDlg::initThresholdWid()
{
    sCfgTh *cth = &(mItem->cTh);
    ui->comboBox->setCurrentIndex(cth->type);
    on_comboBox_currentIndexChanged(cth->type);
}

bool Home_SetDlg::getThresholdWid()
{
    sCfgTh *cth = &(mItem->cTh);
    cth->type = ui->comboBox->currentIndex();
    cth->vol_min = ui->volMinSpin->value();
    cth->vol_max = ui->volMaxSpin->value();
    cth->cur_min = ui->curMinSpin->value()*10;
    cth->cur_max = ui->curMaxSpin->value()*10;
    mItem->user = ui->userEdit->text();

    return true;
}


void Home_SetDlg::setThresholdWid()
{
    sCfgTh *cth = &(mItem->cTh);
    ui->volMinSpin->setValue(cth->vol_min);
    ui->volMaxSpin->setValue(cth->vol_max);
    ui->curMinSpin->setValue(cth->cur_min/10.0);
    ui->curMaxSpin->setValue(cth->cur_max/10.0);
}

void Home_SetDlg::on_comboBox_currentIndexChanged(int index)
{
    bool en = true;
    sCfgTh *cth = &(mItem->cTh);
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
        Cfg::bulid()->writeThreshold();
    }
}

void Home_SetDlg::initCntLab()
{
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
