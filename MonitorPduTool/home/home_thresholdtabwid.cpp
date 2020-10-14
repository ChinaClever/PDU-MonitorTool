#include "home_thresholdtabwid.h"

Home_ThresholdTabWid::Home_ThresholdTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void Home_ThresholdTabWid::initWid()
{
    QString title = tr("报警阈值信息");
    QStringList header;
    header << tr("项目") << tr("当前值") << tr("最小值") << tr("最大值");
    initTableWid(header, 2, title);
}
