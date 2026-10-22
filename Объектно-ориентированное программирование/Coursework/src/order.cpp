#include "order.h"

Order::Order(QObject *parent, int ClientPtr,
             QString MasterPtr, QString ThingToRepair)
    : QObject{parent}
{
    this->ClientRegNumber = ClientPtr;
    this->MasterRegCode = MasterPtr;
    this->ThingToRepair = ThingToRepair;
    this->StatusOfRepair = RepairStatus::InProcess;
}

void Order::SetRepairStatus(RepairStatus Status)
{
    this->StatusOfRepair = Status;
}

int Order::GetClientRegNumber()
{
    return ClientRegNumber;
}

QString Order::GetMasterRegCode()
{
    return MasterRegCode;
}

QString Order::GetThingToRepair()
{
    return this->ThingToRepair;
}

Order::RepairStatus Order::GetStatusOfRepair()
{
    return StatusOfRepair;
}

QString Order::GetStringStatusOfRepair()
{
    switch (this->StatusOfRepair)
    {
    case RepairStatus::InProcess:
        return "В процессе";
        break;
    case RepairStatus::Cancelled:
        return "Отменён";
        break;
    case RepairStatus::Completed:
        return "Выполнен";
        break;
    }
    return "";
}
