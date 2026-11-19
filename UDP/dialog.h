#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <winsock2.h>
#include <stdio.h>
#include "udprx.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private slots:
    void on_pbSend_clicked();   // slot pour les messages sur l'angle
    void on_pbDist_clicked();   // Slot pour mesurer la distance
    void on_pbScan_clicked();   // Slot pour lancer le balayage
    void on_rx(QString);        //


private:
    Ui::Dialog *ui;
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN addr;
    int nbSent, retour;
    UdpRx *pth;
    void updateSocketAddress(); // au cas ou changement d'adresse
};
#endif // DIALOG_H