#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <iostream>

#include "mainwindow.h"

void msgHandler( QtMsgType type, const char* msg )
{
    const char symbols[] = { 'I', 'E', '!', 'X' };
    QString output = QString("[%1] %2").arg( symbols[type] ).arg( msg );
    std::cerr << output.toStdString() << std::endl;
    if( type == QtFatalMsg ) abort();
}

int main(int argc, char **argv)
{
    //qInstallMsgHandler(msgHandler);
    QApplication app(argc, argv);
    MainWindow window;

    qWarning() << "";
    qWarning() << "IPProof-NG (C)";

    window.show();

    return app.exec();
}
