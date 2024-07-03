#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(sl_select_interface(int)));

#if QT_VERSION >= 0x050000
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    obj_refreshList = new QTimer;
    connect(obj_refreshList, SIGNAL(timeout()),SLOT(sl_interfaces_list()));
    obj_refreshList->start(2000);


    obj_refreshTable = new QTimer;
    connect(obj_refreshTable, SIGNAL(timeout()),SLOT(sl_refreshTableWidget()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::m_update_interfaceList()
{
    ui->listWidget->clear();
    int iRow = 0;
    foreach (QNetworkInterface intrface, l_intrfaces)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText( intrface.name());
        ui->listWidget->insertItem(iRow++,newItem);
    }

    if(ui->listWidget->count())
        ui->listWidget->setCurrentRow(0);
}

void MainWindow::sl_interfaces_list()
{

    QList<QNetworkInterface> tmp_list = QNetworkInterface::allInterfaces();

    bool isUpdate = false;
    if(tmp_list.size()!= l_intrfaces.size())
        isUpdate = true;
    else
    {
        for(int index = 0 ; index < tmp_list.size(); index++ )
        {
            if(l_intrfaces[index].humanReadableName()!= tmp_list[index].humanReadableName())
            {
                isUpdate = true;
                break;
            }
        }

    }

    l_intrfaces = QNetworkInterface::allInterfaces();

    if(isUpdate)
        m_update_interfaceList();

}

void MainWindow::sl_select_interface(int index)
{
    if(l_intrfaces.size() > index)
    {
        int row_count = 0;
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setRowCount(0);

        QNetworkInterface obj_intrface = l_intrfaces[index];
        qDebug()<<"Flag = "<<(int)obj_intrface.flags() << obj_intrface.flags();

        QTableWidgetItem *nameLable =  new QTableWidgetItem;
        nameLable->setText("Interface Name");
        ui->tableWidget->insertRow(row_count);
        ui->tableWidget->setItem(row_count,0,nameLable);

        QTableWidgetItem *nameValue =  new QTableWidgetItem;
        nameValue->setText(obj_intrface.humanReadableName());
        ui->tableWidget->setItem(row_count++,1,nameValue);


        QTableWidgetItem *mac_addr =  new QTableWidgetItem;
        mac_addr->setText("MAC Address");
        ui->tableWidget->insertRow(row_count);
        ui->tableWidget->setItem(row_count,0,mac_addr);

        QTableWidgetItem *mac_addrValue =  new QTableWidgetItem;
        mac_addrValue->setText(obj_intrface.hardwareAddress());
        ui->tableWidget->setItem(row_count++,1,mac_addrValue);

        QList<QNetworkAddressEntry> list_addrEntry= obj_intrface.addressEntries();
        foreach (QNetworkAddressEntry tmp_addrEntry, list_addrEntry)
        {

            QString str_ipType;
            if(tmp_addrEntry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                qDebug() <<"IPv4 :";
                str_ipType = "IPv4 ";
            }
            else if(tmp_addrEntry.ip().protocol() == QAbstractSocket::IPv6Protocol)
            {
                qDebug() <<"IPv6:";
                str_ipType = "IPv6 ";
            }
            else if(tmp_addrEntry.ip().protocol() == QAbstractSocket::AnyIPProtocol)
            {
                qDebug() <<"AnyIP:";
                str_ipType = "AnyIP ";
            }
            else
            {
                qDebug() << "Unknown :";
                str_ipType = "IPvUnknown ";
            }

            QTableWidgetItem *ip_addr =  new QTableWidgetItem;
            ip_addr->setText(str_ipType+"Address");
            ui->tableWidget->insertRow(row_count);
            ui->tableWidget->setItem(row_count,0,ip_addr);

            QTableWidgetItem *ip_addrValue =  new QTableWidgetItem;
            ip_addrValue->setText(tmp_addrEntry.ip().toString());
            ui->tableWidget->setItem(row_count++,1,ip_addrValue);

            QTableWidgetItem *ip_netmask =  new QTableWidgetItem;
            ip_netmask->setText(str_ipType+"Netmask");
            ui->tableWidget->insertRow(row_count);
            ui->tableWidget->setItem(row_count,0,ip_netmask);

            QTableWidgetItem *ip_netmaskValue =  new QTableWidgetItem;
            ip_netmaskValue->setText(tmp_addrEntry.netmask().toString());
            ui->tableWidget->setItem(row_count++,1,ip_netmaskValue);

            QTableWidgetItem *ip_broadcast =  new QTableWidgetItem;
            ip_broadcast->setText(str_ipType+"Broadcast");
            ui->tableWidget->insertRow(row_count);
            ui->tableWidget->setItem(row_count,0,ip_broadcast);

            QTableWidgetItem *ip_broadcastValue =  new QTableWidgetItem;
            ip_broadcastValue->setText(tmp_addrEntry.broadcast().toString());
            ui->tableWidget->setItem(row_count++,1,ip_broadcastValue);

            qDebug()<<"tmp_addrEntry IP "<<tmp_addrEntry.ip().toString();
            qDebug()<<"tmp_addrEntry netmask "<<tmp_addrEntry.netmask().toString();
            qDebug()<<"tmp_addrEntry broadcast IP "<<tmp_addrEntry.broadcast().toString();

            obj_refreshTable->start(3500);
        }

    }
}

void MainWindow::sl_refreshTableWidget()
{
    sl_select_interface(ui->listWidget->currentRow());
}
