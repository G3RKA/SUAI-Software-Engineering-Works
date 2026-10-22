#ifndef PLACESMENU_H
#define PLACESMENU_H

#include "place.h"
#include "qstandarditemmodel.h"
#include <QWidget>

namespace Ui {
class PlacesMenu;
}

class PlacesMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PlacesMenu(QWidget *parent = nullptr);
    ~PlacesMenu();

    void ClearInputs();
    Place* GetPlaceByNumber(int);
    Place* GetPlaceByName(QString);
    void SetPlaceStatusByName(QString, bool);

private:
    Ui::PlacesMenu *ui;
    int NumOfPlaces;
    QList<Place*> PlacesList;
    QStandardItemModel* model;

    void SetModelHeader();
    void AddNewPlaceToModel(Place*);
    bool IsPlaceNameInList(QString);
    bool IsPlaceAdressInList(QString);

    void EnablePlace();
    void StopPlace();

private slots:
    void RequestToAddPlace();
    void InfoChanged();
    void RowNumberChanged();

signals:
    void PlaceAdded(QString);
};

#endif // PLACESMENU_H
