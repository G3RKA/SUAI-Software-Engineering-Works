#include "master.h"
#include "qdebug.h"

Master::Master(QObject *parent, QString FIO, QString Position, QString Place)
    : QObject{parent}
{
    this->FIO = FIO;
    this->Position = Position;
    this->Place = Place;
    this->Status = MasterStatus::InWork;
    this->MasterBusy = false;
    this->OrderNumber = -1;

    this->RegCode = Master::FIOnPosToRegCode(FIO, Position);
}

void Master::SetOrder(int OrderNumber)
{
    this->OrderNumber = OrderNumber;
    if (OrderNumber == -1)
    {
        this->MasterBusy = false;
    }
    else
    {
        this->MasterBusy = true;
    }
}

void Master::SetStatus(bool Status)
{
    if (Status)
    {
        this->Status = MasterStatus::InWork;
    }
    else
    {
        this->Status = MasterStatus::Fired;
    }
}

QString Master::GetRegCode()
{
    return this->RegCode;
}

QString Master::GetFIO()
{
    return this->FIO;
}

QString Master::GetPosition()
{
    return this->Position;
}

QString Master::GetPlaceName()
{
    return this->Place;
}

QString Master::GetStatusString()
{
    switch (this->Status)
    {
    case MasterStatus::InWork:
        return "Работает";
        break;
    case MasterStatus::Fired:
        return "Уволен";
        break;
    }
    return "";
}

Master::MasterStatus Master::GetStatus()
{
    return this->Status;
}

bool Master::IsBusy()
{
    return this->MasterBusy;
}

QString Master::GetOrderStatus()
{
    if ((this->OrderNumber == -1) && not(this->MasterBusy))
    {
        return "Нет";
    }
    return "#" + QString::number(this->OrderNumber+1);
}

QString Master::FIOnPosToRegCode(QString FIO, QString Position)
{
    QString RegCode = "";
    if (Position == "Intern")
    {
        RegCode += "IN-";
    }
    else if (Position == "Junior")
    {
        RegCode += "JN-";
    }
    else if (Position == "Middle")
    {
        RegCode += "ML-";
    }
    else if (Position == "Senior")
    {
        RegCode += "SN-";
    }
    else
    {
        RegCode += "OT-";
    }

    int tempCode = 0;
    FIO = FIO.toUpper();
    foreach (auto str, FIO.split(" ")){
        if (str.isEmpty())
        {
            continue;
        }
        tempCode += int(str[0].unicode());
    }
    return RegCode + QString::number(tempCode);
}
