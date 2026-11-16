//#include "dialog.h"

//#include <QApplication>
#include <winsock2.h>
#include <stdio.h>

int main()
{

    //QApplication a(argc, argv);
    //Dialog w;
    //w.show();
    //return QApplication::exec();

    //Spécifique à WINDOWS
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN addr;
    int nbSent, retour;
    char Msg[] = "ANGLE 20";
    char Buffer[100];

    WSAStartup(MAKEWORD(2,0), &WSAData);
    //Fin spécificité WINDOWS
    sock = socket(AF_INET,SOCK_DGRAM,0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.0.3"); //IP Serveur destinataire de la demande de connexion
    addr.sin_port = htons(5000); //Port d'écoute du serveur destinataire

    nbSent=sendto(sock,Msg,strlen(Msg),0,(SOCKADDR*)&addr,sizeof(addr));

    printf("sent %d\n",nbSent);

    retour = recvfrom(sock, Buffer, sizeof(Buffer),0,NULL,NULL);

    printf(Buffer);

    closesocket(sock);
    //Spécifique à WINDOWS
    WSACleanup();
    //Fin spécificité WINDOWS
    exit(-1);
}

