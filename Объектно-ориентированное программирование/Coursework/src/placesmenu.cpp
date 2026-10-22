#include "placesmenu.h"
#include "ui_placesmenu.h"
#include "ordermanipulate.h"
#include <QTimer>

PlacesMenu::PlacesMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlacesMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);

    this->NumOfPlaces = 0;
    auto PlacesTable = ui->PlacesTable;
    PlacesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    PlacesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new QStandardItemModel(0, 4, this);
    SetModelHeader();
    PlacesTable->setModel(model);
    PlacesTable->setWordWrap(true);

    ui->PhoneNumEdit->setInputMask("+7 999 999 99-99;_");
    auto Validator = new QIntValidator(this);
    Validator->setBottom(1);
    ui->NumOfRowEdit_1->setValidator(Validator);

    AddNewPlaceToModel(new Place(nullptr, "На московской", "Пр.Московский", "+7 94324 4342 234"));
    AddNewPlaceToModel(new Place(nullptr, "На ленинском", "Пр.Ленинский", "+7 94324 4542 234"));
    AddNewPlaceToModel(new Place(nullptr, "На петроградcкой", "Пр. Кронверский", "+7 924 4342 234"));

    connect(ui->AddPlace, &QPushButton::clicked, this, &PlacesMenu::RequestToAddPlace);
    connect(ui->EnablePlace, &QPushButton::clicked, this, &PlacesMenu::EnablePlace);
    connect(ui->StopPlace, &QPushButton::clicked, this, &PlacesMenu::StopPlace);

    connect(ui->NameOfPlaceEdit, &QLineEdit::textChanged, this, &PlacesMenu::InfoChanged);
    connect(ui->AdressOfPlaceEdit, &QLineEdit::textChanged, this, &PlacesMenu::InfoChanged);
    connect(ui->PhoneNumEdit, &QLineEdit::textChanged, this, &PlacesMenu::InfoChanged);
    connect(ui->NumOfRowEdit_1, &QLineEdit::textChanged, this, &PlacesMenu::RowNumberChanged);
}

PlacesMenu::~PlacesMenu()
{
    auto ListBegin = PlacesList.begin();
    auto ListEnd = PlacesList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        delete *ListBegin;
    }
    delete ui;
}

void PlacesMenu::ClearInputs()
{
    ui->AddPlace->setDisabled(true);
    ui->EnablePlace->setDisabled(true);
    ui->StopPlace->setDisabled(true);

    ui->NameOfPlaceEdit->clear();
    ui->AdressOfPlaceEdit->clear();
    ui->PhoneNumEdit->clear();
    ui->NumOfRowEdit_1->clear();
}

Place *PlacesMenu::GetPlaceByNumber(int PlaceNumber)
{
    return PlacesList.at(PlaceNumber-1);
}

Place *PlacesMenu::GetPlaceByName(QString PlaceName)
{
    auto ListBegin = PlacesList.begin();
    auto ListEnd = PlacesList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetPlaceName() == PlaceName)
        {
            return *ListBegin;
        }
    }
    return nullptr;
}

void PlacesMenu::SetPlaceStatusByName(QString PlaceName, bool Status)
{
    auto ListBegin = PlacesList.begin();
    auto ListEnd = PlacesList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetPlaceName() == PlaceName)
        {
            break;
        }
    }

    if (Status)
    {
        (*ListBegin)->EnablePlace();
    }
    else
    {
        (*ListBegin)->DisablePlace();
    }
}

void PlacesMenu::SetModelHeader()
{
    model->setHeaderData(0, Qt::Horizontal, "Наименование");
    model->setHeaderData(1, Qt::Horizontal, "Адрес");
    model->setHeaderData(2, Qt::Horizontal, "Номер телефона");
    model->setHeaderData(3, Qt::Horizontal, "Статус");
}

void PlacesMenu::AddNewPlaceToModel(Place* PlaceInfo)
{
    int IndexForAdd = ++this->NumOfPlaces-1;
    model->setItem(IndexForAdd, 0, new QStandardItem(PlaceInfo->GetPlaceName()));
    model->setItem(IndexForAdd, 1, new QStandardItem(PlaceInfo->GetPlaceAdress()));
    model->setItem(IndexForAdd, 2, new QStandardItem(PlaceInfo->GetPhoneNumber()));
    model->setItem(IndexForAdd, 3, new QStandardItem(PlaceInfo->GetStringPlaceStatus()));
    PlacesList.append(PlaceInfo);

    ui->PlacesTable->resizeRowToContents(model->rowCount() - 1);

    QTimer::singleShot(0, this, [PlaceInfo, this]() {
        emit PlaceAdded(PlaceInfo->GetPlaceName());
        OrderManipulate::NewAction("Добавлена новая точка " + PlaceInfo->GetPlaceName() + " по адресу " + PlaceInfo->GetPlaceAdress());
    });

}

void PlacesMenu::RequestToAddPlace()
{
    QString PlaceName = ui->NameOfPlaceEdit->text();
    QString PlaceNumber = ui->PhoneNumEdit->text();
    QString PlaceAdress = ui->AdressOfPlaceEdit->text();
    if (IsPlaceNameInList(PlaceName))
    {
        OrderManipulate::SendErrorMessage("Такое название точки уже существует.");
        return;
    }
    else if (IsPlaceAdressInList(PlaceAdress))
    {
        OrderManipulate::SendErrorMessage("Такой адрес точки уже зарегистрирован.");
        return;
    }
    else
    {
        AddNewPlaceToModel(new Place(nullptr, PlaceName, PlaceAdress, PlaceNumber));
    }
    ClearInputs();
}

bool PlacesMenu::IsPlaceNameInList(QString PlaceName)
{
    auto ListBegin = PlacesList.begin();
    auto ListEnd = PlacesList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetPlaceName() == PlaceName)
        {
            return true;
        }
    }
    return false;
}

bool PlacesMenu::IsPlaceAdressInList(QString PlaceAdress)
{
    auto ListBegin = PlacesList.begin();
    auto ListEnd = PlacesList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetPlaceAdress() == PlaceAdress)
        {
            return true;
        }
    }
    return false;
}

void PlacesMenu::EnablePlace()
{
    int PlaceNumber = ui->NumOfRowEdit_1->text().toInt();
    if (PlaceNumber > NumOfPlaces)
    {
        OrderManipulate::SendErrorMessage("Такой точки не существует.");

        return;
    }
    Place* PlaceInfo = GetPlaceByNumber(PlaceNumber);
    PlaceInfo->EnablePlace();
    model->setItem(PlaceNumber-1, 3, new QStandardItem(PlaceInfo->GetStringPlaceStatus()));
    ClearInputs();

    OrderManipulate::NewAction("Точка " + PlaceInfo->GetPlaceName() + " по адресу " + PlaceInfo->GetPlaceAdress() + " теперь принимает заказы");
}

void PlacesMenu::StopPlace()
{
    int PlaceNumber = ui->NumOfRowEdit_1->text().toInt();
    if (PlaceNumber > NumOfPlaces)
    {
        OrderManipulate::SendErrorMessage("Такой точки не существует.");

        return;
    }
    Place* PlaceInfo = GetPlaceByNumber(PlaceNumber);
    PlaceInfo->DisablePlace();
    model->setItem(PlaceNumber-1, 3, new QStandardItem(PlaceInfo->GetStringPlaceStatus()));
    ClearInputs();

    OrderManipulate::NewAction("Точка " + PlaceInfo->GetPlaceName() + " по адресу " + PlaceInfo->GetPlaceAdress() + " теперь не принимает заказы");
}

void PlacesMenu::InfoChanged()
{
    if (ui->PhoneNumEdit->hasAcceptableInput() && not(ui->NameOfPlaceEdit->text().isEmpty()) && not(ui->AdressOfPlaceEdit->text().isEmpty()))
    {
        ui->AddPlace->setDisabled(false);
    }
    else
    {
        ui->AddPlace->setDisabled(true);
    }
}

void PlacesMenu::RowNumberChanged()
{
    if (ui->NumOfRowEdit_1->hasAcceptableInput() && NumOfPlaces>0)
    {
        ui->EnablePlace->setDisabled(false);
        ui->StopPlace->setDisabled(false);
    }
    else
    {
        ui->EnablePlace->setDisabled(true);
        ui->StopPlace->setDisabled(true);
    }
}
