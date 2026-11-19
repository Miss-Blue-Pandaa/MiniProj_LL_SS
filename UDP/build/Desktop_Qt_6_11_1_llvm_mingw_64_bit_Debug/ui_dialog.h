/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QLineEdit *leIp;
    QLineEdit *lePort;
    QLabel *lbIp;
    QLabel *lbPort;
    QGroupBox *groupBox_2;
    QLineEdit *leAngle;
    QPushButton *pbSend;
    QDoubleSpinBox *dsbDist;
    QLabel *label_2;
    QPushButton *pbDist;
    QLabel *label;
    QGroupBox *groupBox_3;
    QLineEdit *leReponse;
    QTableWidget *tableWidget;
    QPushButton *pbScan;
    QLineEdit *leScan;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(800, 600);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(100, 10, 591, 111));
        leIp = new QLineEdit(groupBox);
        leIp->setObjectName("leIp");
        leIp->setGeometry(QRect(130, 30, 184, 28));
        lePort = new QLineEdit(groupBox);
        lePort->setObjectName("lePort");
        lePort->setGeometry(QRect(130, 70, 113, 28));
        lbIp = new QLabel(groupBox);
        lbIp->setObjectName("lbIp");
        lbIp->setGeometry(QRect(30, 40, 91, 20));
        lbPort = new QLabel(groupBox);
        lbPort->setObjectName("lbPort");
        lbPort->setGeometry(QRect(30, 80, 101, 20));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(100, 130, 591, 121));
        leAngle = new QLineEdit(groupBox_2);
        leAngle->setObjectName("leAngle");
        leAngle->setGeometry(QRect(90, 30, 113, 28));
        pbSend = new QPushButton(groupBox_2);
        pbSend->setObjectName("pbSend");
        pbSend->setGeometry(QRect(310, 30, 90, 29));
        dsbDist = new QDoubleSpinBox(groupBox_2);
        dsbDist->setObjectName("dsbDist");
        dsbDist->setGeometry(QRect(400, 70, 121, 29));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 40, 63, 20));
        pbDist = new QPushButton(groupBox_2);
        pbDist->setObjectName("pbDist");
        pbDist->setGeometry(QRect(30, 70, 191, 29));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(310, 80, 81, 20));
        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(100, 260, 591, 321));
        leReponse = new QLineEdit(groupBox_3);
        leReponse->setObjectName("leReponse");
        leReponse->setGeometry(QRect(20, 80, 551, 31));
        tableWidget = new QTableWidget(groupBox_3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 120, 551, 192));
        pbScan = new QPushButton(groupBox_3);
        pbScan->setObjectName("pbScan");
        pbScan->setGeometry(QRect(170, 40, 90, 29));
        leScan = new QLineEdit(groupBox_3);
        leScan->setObjectName("leScan");
        leScan->setGeometry(QRect(20, 40, 113, 28));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "Configuration R\303\251seau : ", nullptr));
        leIp->setText(QCoreApplication::translate("Dialog", "192.168.184.160", nullptr));
        lePort->setText(QCoreApplication::translate("Dialog", "8002", nullptr));
        lbIp->setText(QCoreApplication::translate("Dialog", "Adresse IP : ", nullptr));
        lbPort->setText(QCoreApplication::translate("Dialog", "Port : ", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "Commande : ", nullptr));
        pbSend->setText(QCoreApplication::translate("Dialog", "SEND", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Angle : ", nullptr));
        pbDist->setText(QCoreApplication::translate("Dialog", "Mesurer la distance", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Distance : ", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Dialog", "R\303\251ponse : ", nullptr));
        leReponse->setText(QCoreApplication::translate("Dialog", "Afficher les messages", nullptr));
        pbScan->setText(QCoreApplication::translate("Dialog", "Balayage", nullptr));
        leScan->setText(QCoreApplication::translate("Dialog", "0 180 10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
