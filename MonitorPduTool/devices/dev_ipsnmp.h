#ifndef DEV_IPSNMP_H
#define DEV_IPSNMP_H

#include <QObject>

class Dev_IpSnmp : public QObject
{
    Q_OBJECT
public:
    explicit Dev_IpSnmp(QObject *parent = nullptr);

signals:

};

#endif // DEV_IPSNMP_H
