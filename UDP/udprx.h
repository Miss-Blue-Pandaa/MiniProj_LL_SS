#ifndef UDPRX_H
#define UDPRX_H

#include <QThread>
#include <winsock2.h>

class UdpRx : public QThread
{
    Q_OBJECT
public:
    explicit UdpRx(SOCKET*);

    virtual void run();
signals:
    void rep(QString);
private:
    SOCKET*p;
};

#endif // UDPRX_H