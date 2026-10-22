#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ordermanipulate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget()->setCursor(Qt::ArrowCursor);

    OrderManipulate::SetRootWidget(this);

    CM = new ClientsMenu(nullptr);
    OM = new OrdersMenu(nullptr);
    MM = new MastersMenu(nullptr);
    TM = new ThingsMenu(nullptr);
    PM = new PlacesMenu(nullptr);
    HM = new HistoryMenu(nullptr);

    connect(ui->ClientsButton, &QPushButton::clicked, CM, &ClientsMenu::show);
    connect(ui->OrdersButton, &QPushButton::clicked, OM, &OrdersMenu::show);
    connect(ui->MastersButton, &QPushButton::clicked, MM, &MastersMenu::show);
    connect(ui->ThingsButton, &QPushButton::clicked, TM, &ThingsMenu::show);
    connect(ui->PlacesButton, &QPushButton::clicked, PM, &PlacesMenu::show);
    connect(ui->HistoryButton, &QPushButton::clicked, HM, &HistoryMenu::show);

    connect(OM, &OrdersMenu::RequestToAddOrder, this, &OrderManipulate::AddOrder);
    connect(OM, &OrdersMenu::RequestToExecuteOrder, this, &OrderManipulate::ExecuteOrder);
    connect(OM, &OrdersMenu::RequestToRemoveOrder, this, &OrderManipulate::RemoveOrder);

    connect(MM, &MastersMenu::RequestToRemoveMaster, this, &OrderManipulate::RemoveMaster);

    connect(PM, &PlacesMenu::PlaceAdded, MM, &MastersMenu::UpdatePlaceList);
    connect(PM, &PlacesMenu::PlaceAdded, TM, &ThingsMenu::UpdatePlaceList);

    connect(this, &MainWindow::NewAction, HM, &HistoryMenu::NewAction);
}

MainWindow::~MainWindow()
{
    delete CM;
    delete OM;
    delete MM;
    delete TM;
    delete PM;
    delete HM;
    delete ui;
}

ClientsMenu* MainWindow::GetClientsMenu()
{
    return CM;
}

OrdersMenu* MainWindow::GetOrdersMenu()
{
    return OM;
}

MastersMenu* MainWindow::GetMastersMenu()
{
    return MM;
}

ThingsMenu* MainWindow::GetThingsMenu()
{
    return TM;
}

PlacesMenu* MainWindow::GetPlacesMenu()
{
    return PM;
}
