#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <QIcon>

#include <iostream>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;

    qWarning() << "";
    qWarning() << "IPProof-NG (C)";

    window.show();
    window.show_dialog();

    return app.exec();
}
