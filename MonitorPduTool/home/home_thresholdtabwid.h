#ifndef HOME_THRESHOLDTABWID_H
#define HOME_THRESHOLDTABWID_H

#include "home_linetabwid.h"

class Home_ThresholdTabWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit Home_ThresholdTabWid(QWidget *parent = nullptr);

signals:

protected:
    void initWid();
    void appendItem(sObjData *dev);

protected slots:
    void timeoutDone();

private:
    sObjData *mData;
};

#endif // HOME_THRESHOLDTABWID_H
