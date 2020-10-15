#include "td_statustabwid.h"

Td_StatusTabWid::Td_StatusTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();

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
