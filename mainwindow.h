#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QNetworkInterface>

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
private:
    Ui::MainWindow *ui;
    QList<QNetworkInterface> l_intrfaces;
};

#endif // MAINWINDOW_H
