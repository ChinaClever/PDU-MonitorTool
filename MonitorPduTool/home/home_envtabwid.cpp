#include "home_envtabwid.h"

Home_EnvTabWid::Home_EnvTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void Home_EnvTabWid::initWid()
{
    QString title = tr("传感器信息");
    QStringList header;
    header << tr("传感器") << tr("监测值") << tr("最小值") << tr("最大值");
    initTableWid(header, 2, title);
}

