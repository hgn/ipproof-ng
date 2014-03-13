#include <QGroupBox>
#include <QPushButton>
#include <QLabel>

#include "measurement-config-dialog.h"
#include "mainwindow.h"




void MeasurementConfigDialog::clicked_start()
{
    int ports[16];

    ports[0] = 5001;
    ports[1] = 5002;

    m_main_window->set_expected_bytes(30000);
    m_main_window->set_listening_ports(ports, 2);

    accept();
}


void MeasurementConfigDialog::add_content_buttons()
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addStretch(1);

    QPushButton* button01 = new QPushButton( "Start" );

    button01->setDefault(true);
    layout->addWidget( button01 );

    connect(button01, SIGNAL( clicked() ), this, SLOT( clicked_start() ) );

    m_main_box->addLayout(layout);
}


void MeasurementConfigDialog::add_content_label()
{
    QLabel *label = new QLabel("Measurement", 0);
    label->setStyleSheet("QLabel { color: #555555; font-size: 32px; font-weight:100; }");
    m_main_box->addWidget(label);
}


void MeasurementConfigDialog::add_selection_area_network_protocol(QHBoxLayout *parent)
{
    QVBoxLayout *box;

    box = new QVBoxLayout;

    QLabel *label = new QLabel("Network Protocol", 0);
    label->setStyleSheet("QLabel { color: #333333; font-size: 16px; font-weight:100; }");
    box->addWidget(label);
    box->addStretch(1);

    parent->addLayout(box);
}


void MeasurementConfigDialog::add_selection_area_transport_protocol(QHBoxLayout *parent)
{
    QVBoxLayout *box;

    box = new QVBoxLayout;

    QLabel *label = new QLabel("Transport Protocol", 0);
    label->setStyleSheet("QLabel { color: #333333; font-size: 16px; font-weight:100; }");
    box->addWidget(label);
    box->addStretch(1);

    parent->addLayout(box);
}


void MeasurementConfigDialog::add_selection_area_ports(QHBoxLayout *parent)
{
    QVBoxLayout *box;

    box = new QVBoxLayout;

    QLabel *label = new QLabel("Ports", 0);
    label->setStyleSheet("QLabel { color: #333333; font-size: 16px; font-weight:100; }");
    box->addWidget(label);

    m_ports_edit = new QLineEdit;
    box->addWidget(m_ports_edit);

    parent->addLayout(box);
}


void MeasurementConfigDialog::add_selection_receive_bytes(QHBoxLayout *parent)
{
    QVBoxLayout *box;

    box = new QVBoxLayout;

    QLabel *label = new QLabel("Read Bytes", 0);
    label->setStyleSheet("QLabel { color: #333333; font-size: 16px; font-weight:100; }");
    box->addWidget(label);

    m_expected_bytes_edit = new QLineEdit;
    box->addWidget(m_expected_bytes_edit);

    parent->addLayout(box);
}


void MeasurementConfigDialog::add_selection_area()
{
    QHBoxLayout *box = new QHBoxLayout;

    add_selection_area_network_protocol(box);
    add_selection_area_transport_protocol(box);
    add_selection_area_ports(box);
    add_selection_receive_bytes(box);


    m_main_box->addLayout(box);

}

MeasurementConfigDialog::MeasurementConfigDialog(MainWindow *parent)
{
    m_main_window = parent;

    resize(900, 400);

    m_main_box = new QVBoxLayout;

    add_content_label();
    add_selection_area();
    m_main_box->addStretch(1);
    add_content_buttons();


    setLayout(m_main_box);
}
