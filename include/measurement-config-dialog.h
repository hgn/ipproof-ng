#ifndef MEASUREMENTCONFIGDIALOG_H
#define MEASUREMENTCONFIGDIALOG_H

#include <QMainWindow>
#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>
#include <QString>

#include "mainwindow.h"


class MeasurementConfigDialog : public QDialog
{
    Q_OBJECT

    public:
        MeasurementConfigDialog(MainWindow *parent = 0);

    public slots:

        void clicked_start();

    private:

        void add_content_label();
        void add_content_logo();
        void add_content_buttons();
        void add_selection_area();
        void add_selection_area_network_protocol(QHBoxLayout *);
        void add_selection_area_transport_protocol(QHBoxLayout *);
        void add_selection_area_ports(QHBoxLayout *);
        void add_selection_receive_bytes(QHBoxLayout *);

        QLineEdit *m_ports_edit;
        QString m_ports;

        QLineEdit *m_expected_bytes_edit;
        QString m_expected_bytes;

        QVBoxLayout *m_main_box;

        MainWindow *m_main_window;
};


#endif // MEASUREMENTCONFIGDIALOG_H
