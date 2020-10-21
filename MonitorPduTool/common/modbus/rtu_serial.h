#ifndef RTU_SERIAL_H
#define RTU_SERIAL_H

#include "config.h"
#include "datapacket.h"

class Rtu_Serial : public QThread
{
    Q_OBJECT
public:
    explicit Rtu_Serial(QObject *parent = nullptr);

    void init(SerialPort *s) {mSerial=s;}
    int readSerial(quint8 *cmd, int secs);
    bool writeSerial(quint8 *cmd, int len);
    int transmit(uchar *sent, int len, uchar *recv, int secs);

protected:
    SerialPort *mSerial;
};

#endif // RTU_SERIAL_H
