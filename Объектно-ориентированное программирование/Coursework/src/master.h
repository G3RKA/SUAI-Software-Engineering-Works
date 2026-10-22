#ifndef MASTER_H
#define MASTER_H

#include <QObject>

class Master : public QObject
{
    Q_OBJECT
public:
    enum class MasterStatus
    {
        InWork,
        Fired
    };

    explicit Master(QObject *parent = nullptr, QString FIO="", QString Position="", QString Place="");
    static QString FIOnPosToRegCode(QString, QString);

    void SetOrder(int);
    void SetStatus(bool);

    QString GetRegCode();
    QString GetFIO();
    QString GetPosition();
    QString GetPlaceName();
    MasterStatus GetStatus();
    QString GetStatusString();
    bool IsBusy();
    QString GetOrderStatus();

private:
    QString RegCode;
    QString FIO;
    QString Position;
    QString Place;
    MasterStatus Status;
    bool MasterBusy;
    int OrderNumber;
};

#endif // MASTER_H
