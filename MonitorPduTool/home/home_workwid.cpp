/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "home_workwid.h"
#include "ui_home_workwid.h"

Home_WorkWid::Home_WorkWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_WorkWid)
{
    ui->setupUi(this);

    createWid();
    initLayout();
}

Home_WorkWid::~Home_WorkWid()
{
    delete ui;
}

void Home_WorkWid::createWid()
{
    mSetDlg = new Home_SetDlg(this);
    mManualDlg = new Home_ManualDlg(this);

    sDataPacket *packet = sDataPacket::bulid();
    mDev = packet->getDev();
    mPro = packet->getPro();
    mItem = Cfg::bulid()->item;
    mPro->step = Test_End;

    timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutDone()));
}

void Home_WorkWid::initLayout()
{
    QPalette pl = ui->textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    ui->textEdit->setPalette(pl);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff ); //垂直滚动条隐藏
    ui->textEdit->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );//水平滚动条隐藏

    QGridLayout *gridLayout = new QGridLayout(this->parentWidget());
    gridLayout->setContentsMargins(0, 7, 0, 0);
    gridLayout->addWidget(this);
}

void Home_WorkWid::setTextColor()
{
    QColor color("black");
    bool pass = mPro->pass.first();
    if(!pass) color = QColor("red");
    ui->textEdit->moveCursor(QTextCursor::Start);

    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(color);// 前景色(即字体色)设为color色
    QTextCursor cursor = ui->textEdit->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textEdit->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
}

void Home_WorkWid::insertText()
{
    if(mPro->status.size()) {
        setTextColor();
        ui->textEdit->insertPlainText(mPro->status.first() +"\n");
        mPro->status.removeFirst();
        mPro->pass.removeFirst();
    }
}

void Home_WorkWid::updateCnt()
{
    sCount *cnt = &(mItem->cnt);
    ui->okLcd->display(cnt->ok);
    ui->allLcd->display(cnt->all);
    ui->errLcd->display(cnt->err);

    QString str = "0";
    if(cnt->all) {
        double value = cnt->ok*1.0 / cnt->all;
        str = QString::number(value,'f',1) +"%";
    }
    ui->passLcd->display(str);
}


QString Home_WorkWid::getTime()
{
    QTime t(0,0,0,0);
    t = t.addSecs(mPro->startTime.secsTo(QTime::currentTime()));
    return  tr("%1").arg(t.toString("mm:ss"));
}

void Home_WorkWid::updateTime()
{
    QString str = getTime();
    QString style = "background-color:yellow; color:rgb(0, 0, 0);";
    style += "font:100 34pt \"微软雅黑\";";

    ui->timeLab->setText(str);
    ui->timeLab->setStyleSheet(style);

    str = mPro->startTime.toString("hh:mm:ss");
    ui->startLab->setText(str);
    ui->startBtn->setText(tr("结束测试"));
}

void Home_WorkWid::updateResult()
{
    QString style;
    QString str = tr("---");
    switch (mPro->result) {
    case Test_Pass:
        str = tr("成功");
        style = "background-color:green; color:rgb(255, 255, 255);";
        break;
    case Test_Fail:
        str = tr("失败");
        style = "background-color:red; color:rgb(255, 255, 255);";
        break;
    }
    style += "font:100 34pt \"微软雅黑\";";

    ui->timeLab->setText(str);
    ui->timeLab->setStyleSheet(style);

    str = QTime::currentTime().toString("hh:mm:ss");
    ui->endLab->setText(str);
    mPro->step = Test_End;

    ui->startBtn->setText(tr("开始测试"));
}

void Home_WorkWid::updateWid()
{
    char *ptr = mDev->devType.sn;
    ui->snLab->setText(ptr);

    ptr = mDev->devType.dev_type;
    ui->devLab->setText(ptr);
    ui->userLab->setText(mItem->user);

    if(mPro->step < Test_Over) {
        updateTime();
    } else if(mPro->step < Test_End){
        updateResult();
    }
}

void Home_WorkWid::on_setBtn_clicked()
{
    mSetDlg->exec();
}

void Home_WorkWid::timeoutDone()
{
    if(mPro->step) {
        insertText();
        updateWid();
        updateCnt();
    }
}

bool Home_WorkWid::initSerial()
{
    QString str;
    sSerial *coms = &(mItem->coms);
    mDev->id = ui->addrSpin->value();

    bool ret = coms->source->isOpened();
    if(!ret){MsgBox::critical(this, tr("请先打开标准源串口")); return ret;}

    ret = coms->ser1->isOpened();
    if(!ret){MsgBox::critical(this, tr("请先打级联串口 1")); return ret;}

    //    ret = coms->ser2->isOpened();
    //    if(!ret){MsgBox::critical(this, tr("请先打级联串口 2")); return ret;}

    return ret;
}

bool Home_WorkWid::initWid()
{
    ui->textEdit->clear();
    bool ret = initSerial();
    if(ret) ret = mManualDlg->exec();
    if(!ret) {
        MsgBox::warning(this, tr("经人工确认，设备出现问题，测试结束！！！"));
    }

    return ret;
}

void Home_WorkWid::on_startBtn_clicked()
{
    if(mPro->step == Test_End) {
        if(initWid()) {

        }
    } else {
        mPro->result = Test_Fail;
        updateResult();
    }
}

void Home_WorkWid::on_readBtn_clicked()
{
    bool ret = initSerial();
    if(ret) {
        ui->textEdit->clear();
        Test_DataRead::bulid(this)->start();
        MsgBox::information(this, tr("已开始读取设备数据，请等待5抄！！！"));
    }
}
