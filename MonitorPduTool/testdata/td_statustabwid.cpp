/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "td_statustabwid.h"

Td_StatusTabWid::Td_StatusTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    mPro = sDataPacket::bulid()->getPro();
}


void Td_StatusTabWid::initWid()
{
    QStringList header;
    QString title = tr("校准数据列表");
    header << tr("时间") << tr("结果") << tr("测试项");
    initTableWid(header, 0, title);

    setColumnWidth(0, 200);
    setColumnWidth(1, 130);
    QGridLayout *gridLayout = new QGridLayout(this->parentWidget());
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
}


void Td_StatusTabWid::appendItem()
{
    QStringList listStr;
    listStr << mPro->time;
    switch (mPro->pass) {
    case Test_Fail: listStr << "×"; break;
    case Test_Pass: listStr << "√"; break;
    default: listStr << " "; break;
    }

    listStr << mPro->item.first();
    insertRow(0, listStr);

    mPro->item.removeFirst();
    if(mPro->pass == Test_Fail)
        setAlarmBackgroundColor(0);
}

void Td_StatusTabWid::timeoutDone()
{
    if(mPro->step) {
        if(mPro->item.size())
            appendItem();
    } else {
        delTable();
    }
}
