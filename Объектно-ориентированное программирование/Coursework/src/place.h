#ifndef PLACE_H
#define PLACE_H

#include <QObject>

class Place : public QObject
{
    Q_OBJECT
public:
    enum class PlaceStatus
    {
        InWork,
        Suspended
    };

    explicit Place(QObject *parent = nullptr, QString PlaceName = "", QString PlaceAdress = "", QString PhoneNumber = "", PlaceStatus Status = PlaceStatus::InWork);

    QString GetPlaceName();
    QString GetPlaceAdress();
    QString GetPhoneNumber();
    PlaceStatus GetPlaceStatus();
    QString GetStringPlaceStatus();

    void EnablePlace();
    void DisablePlace();

private:
    QString PlaceName;
    QString PlaceAdress;
    QString PhoneNumber;
    PlaceStatus Status;

};

#endif // PLACE_H
