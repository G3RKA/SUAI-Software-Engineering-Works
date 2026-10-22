#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientsmenu.h"
#include "mastersmenu.h"
#include "ordersmenu.h"
#include "placesmenu.h"
#include "thingsmenu.h"
#include "historymenu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ClientsMenu* GetClientsMenu();
    OrdersMenu* GetOrdersMenu();
    MastersMenu* GetMastersMenu();
    ThingsMenu* GetThingsMenu();
    PlacesMenu* GetPlacesMenu();

private:
    Ui::MainWindow* ui;
    ClientsMenu* CM;
    OrdersMenu* OM;
    MastersMenu* MM;
    ThingsMenu* TM;
    PlacesMenu* PM;

    HistoryMenu* HM;

signals:
    void NewAction(QString);
};
#endif // MAINWINDOW_H
