#include "ordermanipulate.h"
#include "qmessagebox.h"

MainWindow* OrderManipulate::RootWidget = nullptr;

OrderManipulate::OrderManipulate(QWidget* parent)
    : QWidget{parent}
{}

void OrderManipulate::SetRootWidget(MainWindow* InRootWidget)
{
    RootWidget = InRootWidget;
}

void OrderManipulate::SendErrorMessage(QString ErrorMessage)
{
    QMessageBox msgBox;
    msgBox.setText(ErrorMessage);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
}

void OrderManipulate::AddOrder(Order* OrderInfo)
{
    QString MasterRegCode = OrderInfo->GetMasterRegCode();
    QString ThingName = OrderInfo->GetThingToRepair();
    if (not(RootWidget->GetClientsMenu()->IsClientInList(OrderInfo->GetClientRegNumber())))
    {
        OrderManipulate::SendErrorMessage("Такого клиента не существует.");

        delete OrderInfo;
        return;
    }
    if (not(RootWidget->GetMastersMenu()->IsMasterInList(MasterRegCode)))
    {
        OrderManipulate::SendErrorMessage("Такого мастера не существует.");

        delete OrderInfo;
        return;
    }
    if (not(RootWidget->GetThingsMenu()->IsThingNameInList(ThingName)))
    {
        OrderManipulate::SendErrorMessage("Данная вещь не зарегистрирована.");

        delete OrderInfo;
        return;
    }
    Thing* ThingInfo = RootWidget->GetThingsMenu()->GetThingByName(ThingName);
    if (RootWidget->GetPlacesMenu()->GetPlaceByName(ThingInfo->GetPlaceName())->GetPlaceStatus() == Place::PlaceStatus::Suspended)
    {
        OrderManipulate::SendErrorMessage("Данная точка не принимает заказы.");

        delete OrderInfo;
        return;
    }
    if (ThingInfo->IsThingInOrder())
    {
        OrderManipulate::SendErrorMessage("Данная вещь уже в работе.");

        delete OrderInfo;
        return;
    }
    Master* MasterInfo = RootWidget->GetMastersMenu()->GetMasterByRegCode(MasterRegCode);
    if (MasterInfo->GetStatus() == Master::MasterStatus::Fired)
    {
        OrderManipulate::SendErrorMessage("Данный мастер уже уволен.");

        return;
    }
    if (MasterInfo->IsBusy())
    {
        OrderManipulate::SendErrorMessage("Мастер уже занят.");

        delete OrderInfo;
        return;
    }
    if (ThingInfo->GetPlaceName() != MasterInfo->GetPlaceName())
    {
        OrderManipulate::SendErrorMessage("Места мастера и вещи не совпадают.");

        delete OrderInfo;
        return;
    }

    int OrderNumber = RootWidget->GetOrdersMenu()->GetSizeOfList();

    RootWidget->GetOrdersMenu()->AddNewOrderToModel(OrderInfo);
    RootWidget->GetMastersMenu()->SetMasterBusyStatusByRegCode(MasterRegCode, OrderNumber);
    RootWidget->GetThingsMenu()->SetOrderStatusByName(ThingName, OrderNumber);
    RootWidget->GetOrdersMenu()->ClearInputs();
}

void OrderManipulate::ExecuteOrder(int OrderNumber)
{

    if (OrderNumber > RootWidget->GetOrdersMenu()->GetSizeOfList())
    {
        OrderManipulate::SendErrorMessage("Такого заказа не существует.");

        return;
    }
    Order* OrderInfo = RootWidget->GetOrdersMenu()->GetOrderByNumber(OrderNumber);
    if (OrderInfo->GetStatusOfRepair() != Order::RepairStatus::InProcess)
    {
        OrderManipulate::SendErrorMessage("Данный заказ уже закончен.");

        return;
    }    

    RootWidget->GetMastersMenu()->SetMasterBusyStatusByRegCode(OrderInfo->GetMasterRegCode(), -1);
    RootWidget->GetOrdersMenu()->SetOrderAsCompleted(OrderNumber);
    RootWidget->GetThingsMenu()->SetOrderStatusByName(OrderInfo->GetThingToRepair(), -1);
    RootWidget->GetOrdersMenu()->ClearInputs();
}

void OrderManipulate::RemoveOrder(int OrderNumber)
{
    if (OrderNumber > RootWidget->GetOrdersMenu()->GetSizeOfList())
    {
        OrderManipulate::SendErrorMessage("Такого заказа не существует.");

        return;
    }
    Order* OrderInfo = RootWidget->GetOrdersMenu()->GetOrderByNumber(OrderNumber);
    if (OrderInfo->GetStatusOfRepair() != Order::RepairStatus::InProcess)
    {
        OrderManipulate::SendErrorMessage("Данный заказ уже закончен.");

        return;
    }
    RootWidget->GetOrdersMenu()->CancelOrder(OrderNumber);
    RootWidget->GetMastersMenu()->SetMasterBusyStatusByRegCode(OrderInfo->GetMasterRegCode(), -1);
    RootWidget->GetThingsMenu()->SetOrderStatusByName(OrderInfo->GetThingToRepair(), -1);
    RootWidget->GetOrdersMenu()->ClearInputs();
}

void OrderManipulate::RemoveMaster(QString RegCode)
{
    if (not(RootWidget->GetMastersMenu()->IsMasterInList(RegCode)))
    {
        OrderManipulate::SendErrorMessage("Такого мастера не существует.");

        return;
    }
    Master* MasterInfo = RootWidget->GetMastersMenu()->GetMasterByRegCode(RegCode);
    if (MasterInfo->IsBusy())
    {
        OrderManipulate::SendErrorMessage("У мастера есть не выполненный заказ.");

        return;
    }
    if (MasterInfo->GetStatus() == Master::MasterStatus::Fired)
    {
        OrderManipulate::SendErrorMessage("Данный мастер уже уволен.");

        return;
    }
    RootWidget->GetMastersMenu()->FireMaster(RegCode);
    RootWidget->GetMastersMenu()->ClearInputs();
}

void OrderManipulate::NewAction(QString InMessage)
{
    RootWidget->NewAction(InMessage);
}
