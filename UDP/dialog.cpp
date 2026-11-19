#include "dialog.h"
#include "ui_dialog.h"
#include <QRegularExpression>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Configuration du TableWidget pour le SCAN (2 colonnes : Angle et Distance)
    ui->tableWidget->setColumnCount(2);
    QStringList headers;
    headers << "Angle (°)" << "Distance (cm)";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Spécifique à WINDOWS
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;

    pth = new UdpRx(&sock);
    QObject::connect(pth, SIGNAL(rep(QString)), this, SLOT(on_rx(QString)));
    pth->start();
}

Dialog::~Dialog()
{
    closesocket(sock);
    WSACleanup();
    delete ui;
}

// Actualisation de l'adresse IP et du port avant chaque envoi
void Dialog::updateSocketAddress()
{
    addr.sin_addr.s_addr = inet_addr(ui->leIp->text().toStdString().c_str());
    addr.sin_port = htons(ui->lePort->text().toInt());
}

// Envoi de la commande ANGLE
void Dialog::on_pbSend_clicked()
{
    updateSocketAddress();
    QString cmd = "ANGLE " + ui->leAngle->text();
    nbSent = sendto(sock, cmd.toStdString().c_str(), cmd.length(), 0, (SOCKADDR*)&addr, sizeof(addr));
}

// Envoi de la commande DIST (Mesurer la distance)
void Dialog::on_pbDist_clicked()
{
    updateSocketAddress();
    QString cmd = "DIST";
    nbSent = sendto(sock, cmd.toStdString().c_str(), cmd.length(), 0, (SOCKADDR*)&addr, sizeof(addr));
}

// Envoi de la commande SCAN (Balayage)
void Dialog::on_pbScan_clicked()
{
    updateSocketAddress();
    QString cmd = "SCAN " + ui->leScan->text(); // Récupère "0 180 10" depuis le QLineEdit leScan
    nbSent = sendto(sock, cmd.toStdString().c_str(), cmd.length(), 0, (SOCKADDR*)&addr, sizeof(addr));
}

// Réception des trames UDP et affichage
void Dialog::on_rx(QString mesg) {
    QString messageEnCours = mesg.trimmed();

    // Si c'est une réponse de distance
    if (messageEnCours.startsWith("DIST")) {
        QStringList parts = messageEnCours.split(" ", Qt::SkipEmptyParts);
        if (parts.size() >= 2) {
            ui->dsbDist->setValue(parts.at(1).toDouble());
        }
    }
    // Si c'est un balayage (SCAN) : dans tableWidget
    else if (messageEnCours.contains("END") || messageEnCours.contains("\n")) {
        ui->tableWidget->setRowCount(0);

        QStringList lignes = messageEnCours.split("\n", Qt::SkipEmptyParts);
        int rowIdx = 0;
        for (const QString &ligne : lignes) {
            QString ligneCourante = ligne.trimmed();
            if (ligneCourante == "END") break;

            QStringList elements = ligneCourante.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            if (elements.size() >= 2) {
                ui->tableWidget->insertRow(rowIdx);
                ui->tableWidget->setItem(rowIdx, 0, new QTableWidgetItem(elements.at(0)));
                ui->tableWidget->setItem(rowIdx, 1, new QTableWidgetItem(elements.at(1)));
                rowIdx++;
            }
        }
    }
    // Tous les autres messages vont dans leReponse
    else {
        ui->leReponse->setText(messageEnCours);
    }
}

