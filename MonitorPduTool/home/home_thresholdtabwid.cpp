/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "home_thresholdtabwid.h"

Home_ThresholdTabWid::Home_ThresholdTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    sDevData *dev = sDataPacket::bulid()->getDev();
    mData = &(dev->line);
}

void Home_ThresholdTabWid::initWid()
{
    QString title = tr("报警阈值信息");
    QStringList header;
    header << tr("项目") << tr("当前值") << tr("最小值") << tr("最大值");
    initTableWid(header, 6, title);
}

void Home_ThresholdTabWid::setDataUnit(int id, sDataUnit &unit)
{
    double rate = COM_RATE_CUR;
    QString suffix = "A";
    QString str = tr("电流");
    if(id < 3) {
        rate = 1;
        suffix = "V";
        str = tr("电压");
    }

    for(int i=0; i<unit.size; ++i) {
        QStringList listStr;

        listStr << str;
        listStr << QString::number(unit.value[i]/rate,'f',2)+suffix;
        listStr << QString::number(unit.min[i]/rate,'f',2)+suffix;
        listStr << QString::number(unit.max[i]/rate,'f',2)+suffix;
        setTableRow(id+i, listStr);

        if((unit.value[i] < unit.min[i]) || (unit.value[i] > unit.max[i])) {
            unit.alarm[i] = 2;
            setAlarmBackgroundColor(id+i);
        } else {
            unit.alarm[i] = 0;
            setNormalBackgroundColor(id+i);
        }
    }
}

void Home_ThresholdTabWid::appendItem(sObjData *dev)
{
    setDataUnit(0, dev->vol);
    setDataUnit(3, dev->cur);
}

void Home_ThresholdTabWid::timeoutDone()
{
    clearTable();
    if(mData->size) {
        appendItem(mData);
    }
}
