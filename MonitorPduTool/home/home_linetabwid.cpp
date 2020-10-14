#include "home_linetabwid.h"

Home_LineTabWid::Home_LineTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void Home_LineTabWid::initWid()
{
    QString title = tr("相数据列表");
    QStringList header;
    header << tr("开关") << tr("电流") << tr("电压") << tr("有功功率")  << tr("功率因数")<< tr("电能");
    initTableWid(header, 3, title);
}
