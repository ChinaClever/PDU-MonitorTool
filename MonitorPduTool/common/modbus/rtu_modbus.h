#ifndef RTU_MODBUS_H
#define RTU_MODBUS_H

#include "rtu_write.h"

class Rtu_Modbus : public Rtu_Write
{
    Q_OBJECT
public:
    explicit Rtu_Modbus(QObject *parent = nullptr);

signals:

};

#endif // RTU_MODBUS_H
