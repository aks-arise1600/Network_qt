#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(sl_select_interface(int)));

    sl_interfaces_list();

//    QTimer::singleShot(3000,ui->listWidget,SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sl_interfaces_list()
{
    ui->listWidget->clear();
    int iRow = 0;
    l_intrfaces = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface intrface, l_intrfaces)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText( intrface.name());
        ui->listWidget->insertItem(iRow++,newItem);
    }
}

void MainWindow::sl_select_interface(int index)
{
    ui->plainTextEdit->clear();
    if(l_intrfaces.size() > index)
    {
        QNetworkInterface obj_intrface = l_intrfaces[index];
        ui->plainTextEdit->appendPlainText("Name        : "+obj_intrface.name());
        ui->plainTextEdit->appendPlainText("MAC Address : "+obj_intrface.hardwareAddress());
        ui->plainTextEdit->appendPlainText("IP4 Address : "+obj_intrface.allAddresses().at(obj_intrface.index()).toString());
        QList <QHostAddress> list = obj_intrface.allAddresses();
        for(int nIter = 0; nIter < list.size() ; nIter++)
        {
        if(!list[nIter].isLoopback())
                  if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                qDebug() << list[nIter].toString();
        }

    }
}
