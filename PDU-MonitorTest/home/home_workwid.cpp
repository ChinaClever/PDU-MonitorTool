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

    mFirst = 0;
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
    mCoreThread = new Test_CoreThread(this);

    mPacket = sDataPacket::bulid();
    mDev = mPacket->getDev();
    mPro = mPacket->getPro();
    mItem = Cfg::bulid()->item;
    mPro->step = Test_End;

    ui->readBtn->setHidden(true);
    mDev->id = Cfg::bulid()->initAddr();
    ui->addrSpin->setValue(mDev->id);
    ui->vrefCheck->setChecked(mItem->vref);

    timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutDone()));
}

void Home_WorkWid::initLayout()
{
    QPalette pl = ui->textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    ui->textEdit->setPalette(pl);
    //ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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
        QString str = QString::number(mId++) + "、"+ mPro->status.first() + "\n";
        ui->textEdit->insertPlainText(str);
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
        double value = cnt->ok*100.0 / cnt->all;
        str = QString::number(value,'f',0) +"%";
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
    ui->endLab->setText("---");
}

void Home_WorkWid::updateResult()
{
    QString style;
    QString str = tr("---");
    if (Test_Fail == mPro->result) {
        str = tr("失败");
        style = "background-color:red; color:rgb(255, 255, 255);";
    } else {
        str = tr("成功");
        style = "background-color:green; color:rgb(255, 255, 255);";
    }
    style += "font:100 34pt \"微软雅黑\";";

    ui->timeLab->setText(str);
    ui->timeLab->setStyleSheet(style);

    str = QTime::currentTime().toString("hh:mm:ss");
    ui->endLab->setText(str);
    mPro->step = Test_End;

    ui->groupBox_4->setEnabled(true);
    ui->startBtn->setText(tr("开始测试"));
    ui->startBtn->setFocus(); //设置默认焦点
    //ui->startBtn->setDefault(true);//设置默认按钮
    //ui->startBtn->setShortcut(Qt::Key_Return);
    //ui->startBtn->setShortcut(Qt::Key_Enter);
    //ui->startBtn->setShortcut(Qt::Key_Backspace);
}

void Home_WorkWid::updateWid()
{
    QString str = mDev->devType.sn;
    ui->snLab->setText(str);

    str = mDev->devType.dev_type;
    ui->devLab->setText(str);
    ui->userLab->setText(mItem->user);

    if(mPro->step < Test_Over) {
        updateTime();
    } else if(mPro->step < Test_End){
        updateResult();
    }
}

void Home_WorkWid::on_setBtn_clicked()
{
    mSetDlg->initCntLab();
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
    QString str;  mId = 1;
    sSerial *coms = &(mItem->coms);
    mDev->id = ui->addrSpin->value();
    mItem->eleCheck = ui->eleCheck->isChecked();
    mItem->vref = ui->vrefCheck->isChecked();
    Cfg::bulid()->setAddr(mDev->id);

    bool ret = coms->ser2->isOpened();
    if(!ret){MsgBox::critical(this, tr("请先打 LINK 级联串")); return ret;}
    if(mPro->step < Test_End) {
        ret = coms->source->isOpened();
        if(!ret){MsgBox::critical(this, tr("请先打开 SI-PDU 参考源串口")); return ret;}
        //ret = coms->ser1->isOpened();
        //if(!ret){MsgBox::critical(this, tr("请先打 SER 级联口")); return ret;}
    }

    return ret;
}

bool Home_WorkWid::initWid()
{
    bool ret = initSerial();
    if(!ret) return ret;

    if(!mFirst) {
        ret = MsgBox::information(this, tr("请确认首件测试，人工已验证通过？"));
        if(ret) mFirst++; else return false;
        on_setBtn_clicked();
    }

    if(mItem->user.isEmpty()) {
        MsgBox::critical(this, tr("请先填写客户名称！"));
        return false;
    }

    if(mItem->cnt.num < 1) {
        MsgBox::critical(this, tr("请先填写订单剩余数量！"));
        return false;
    }

    if(mItem->cTh.enModify) {
        ret = MsgBox::question(this, tr("测试软件会自动修改，设备报警阈值，请确认？"));
    }

    if(ret) ret = ui->guideCheck->isChecked();
    if(ret) ret = mManualDlg->exec(); else ret = true;
    if(ret) {
        mPacket->init();
        emit startSig();
        ui->textEdit->clear();
        ui->groupBox_4->setEnabled(false);
    } else {
        MsgBox::warning(this, tr("经人工确认，设备出现问题，测试结束！！！"));
    }

    return ret;
}

void Home_WorkWid::on_startBtn_clicked()
{
    if(mPro->step == Test_End) {
        if(initWid()) mCoreThread->start();
    } else {
        bool ret = MsgBox::question(this, tr("确定需要提前结束？"));
        if(ret) {
            mPro->result = Test_Fail;
            updateResult();
        }
    }
}

void Home_WorkWid::on_readBtn_clicked()
{
    mPro->step = Collect_Start;
    bool ret = initSerial();
    if(ret) {
        ui->textEdit->clear();
        Test_DevRead::bulid(this)->start();
        //MsgBox::information(this, tr("已开始读取设备数据，请等待5抄！！！"));
    }
}
