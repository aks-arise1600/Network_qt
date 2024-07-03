#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QNetworkInterface>
#include <QTableWidgetItem>
#include <QFlags>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void sl_interfaces_list();
    void sl_select_interface(int index);
    void sl_refreshTableWidget();
private:
    Ui::MainWindow *ui;
    QList<QNetworkInterface> l_intrfaces;
    void m_update_interfaceList();
    QTimer *obj_refreshList = 0;
    QTimer *obj_refreshTable = 0;

};

#endif // MAINWINDOW_H
