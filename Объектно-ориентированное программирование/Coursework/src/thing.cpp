#include "thing.h"

Thing::Thing(QObject *parent, QString ThingName, QString PlaceName): QObject{parent}
{
    this->ThingName = ThingName;
    this->PlaceName = PlaceName;
    this->Status = ThingStatus::None;
    this->ThingInOrder = false;
    this->OrderNumber = -1;
}

QString Thing::GetThingName()
{
    return ThingName;
}

QString Thing::GetPlaceName()
{
    return PlaceName;
}

QString Thing::GetThingStatusString()
{
    switch (this->Status)
    {
    case ThingStatus::InWork:
        return "В ремонте";
        break;
    case ThingStatus::None:
        return "Отсутствует";
        break;
    }
    return "";
}

bool Thing::IsThingInOrder()
{
    switch (this->Status)
    {
    case ThingStatus::InWork:
        return true;
        break;
    case ThingStatus::None:
        return false;
        break;
    }
    return false;
}

void Thing::SetOrder(int OrderNumber)
{
    this->OrderNumber = OrderNumber;
    switch (this->OrderNumber)
    {
    case -1:
        this->Status = ThingStatus::None;
        break;
    default:
        this->Status = ThingStatus::InWork;
        break;
    }
}
