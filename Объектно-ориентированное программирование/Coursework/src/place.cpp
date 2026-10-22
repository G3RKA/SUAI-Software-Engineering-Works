#include "place.h"


Place::Place(QObject *parent, QString PlaceName, QString PlaceAdress, QString PhoneNumber, PlaceStatus Status): QObject{parent}
{
    this->PlaceName=PlaceName;
    this->PlaceAdress = PlaceAdress;
    this->PhoneNumber=PhoneNumber;
    this->Status=Status;
}

QString Place::GetPlaceName()
{
    return PlaceName;
}

QString Place::GetPlaceAdress()
{
    return PlaceAdress;
}

QString Place::GetPhoneNumber()
{
    return PhoneNumber;
}

Place::PlaceStatus Place::GetPlaceStatus()
{
    return Status;
}

QString Place::GetStringPlaceStatus()
{
    switch (this->Status)
    {
    case PlaceStatus::InWork:
        return "Работает";
        break;
    case PlaceStatus::Suspended:
        return "Приостановлен";
        break;
    }
    return "";
}

void Place::EnablePlace()
{
    this->Status = PlaceStatus::InWork;
}

void Place::DisablePlace()
{
    this->Status = PlaceStatus::Suspended;
}
