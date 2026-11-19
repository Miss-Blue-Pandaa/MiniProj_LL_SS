#include "dialog.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return QApplication::exec();
}

