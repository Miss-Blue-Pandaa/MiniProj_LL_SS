#include "udprx.h"

UdpRx::UdpRx(SOCKET *parent)
    : QThread{NULL}
{
    p=(SOCKET*)parent;
}
void UdpRx::run(){
    char Buffer[50];
    int retour;
    while(1){
        retour = recvfrom(*p, Buffer, sizeof(Buffer),0,NULL,NULL);
        Buffer[retour]=0;

        msleep(500);
        emit rep(QString(Buffer));
    }
}
