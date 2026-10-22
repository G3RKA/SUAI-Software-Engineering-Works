#ifndef THING_H
#define THING_H

#include <QObject>

class Thing : public QObject
{
    Q_OBJECT
public:
    enum class ThingStatus
    {
        InWork,
        None
    };

    explicit Thing(QObject *parent = nullptr, QString ThingName="", QString PlaceName="");

    QString GetThingName();
    QString GetPlaceName();
    QString GetThingStatusString();
    bool IsThingInOrder();

    void SetOrder(int);
private:
    QString ThingName;
    QString PlaceName;
    ThingStatus Status;
    bool ThingInOrder;
    int OrderNumber;

};

#endif // THING_H
