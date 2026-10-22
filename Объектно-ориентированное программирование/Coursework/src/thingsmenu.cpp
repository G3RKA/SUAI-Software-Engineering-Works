#include "thingsmenu.h"
#include "ui_thingsmenu.h"
#include "ordermanipulate.h"

ThingsMenu::ThingsMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThingsMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);

    this->NumOfThings = 0;
    auto ThingsTable = ui->ThingsTable;
    ThingsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ThingsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new QStandardItemModel(0, 3, this);
    SetModelHeader();
    ThingsTable->setModel(model);
    ThingsTable->setWordWrap(true);

    connect(ui->AddThing, &QPushButton::clicked, this, &ThingsMenu::RequestToAddThing);
    connect(ui->ThingNameEdit, &QLineEdit::textChanged, this, &ThingsMenu::InfoChanged);
}

ThingsMenu::~ThingsMenu()
{
    auto ListBegin = ThingsList.begin();
    auto ListEnd = ThingsList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        delete *ListBegin;
    }
    delete ui;
}

void ThingsMenu::ClearInputs()
{
    ui->AddThing->setDisabled(true);

    ui->ThingNameEdit->clear();
    ui->PlaceComboBox->setCurrentIndex(0);
}

void ThingsMenu::SetOrderStatusByName(QString ThingName, int OrderNumber)
{
    auto ListBegin = ThingsList.begin();
    auto ListEnd = ThingsList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetThingName() == ThingName)
        {
            break;
        }
    }

    (*ListBegin)->SetOrder(OrderNumber);
    model->setItem(ListBegin-ThingsList.begin(), 2, new QStandardItem((*ListBegin)->GetThingStatusString()));
}

bool ThingsMenu::IsThingNameInList(QString ThingName)
{
    auto ListBegin = ThingsList.begin();
    auto ListEnd = ThingsList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetThingName() == ThingName)
        {
            return true;
        }
    }
    return false;
}

Thing* ThingsMenu::GetThingByName(QString ThingName)
{
    auto ListBegin = ThingsList.begin();
    auto ListEnd = ThingsList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetThingName() == ThingName)
        {
            return *ListBegin;
        }
    }
    return nullptr;
}

void ThingsMenu::AddNewThingToModel(Thing* ThingInfo)
{
    int IndexForAdd = ++this->NumOfThings-1;
    model->setItem(IndexForAdd, 0, new QStandardItem(ThingInfo->GetThingName()));
    model->setItem(IndexForAdd, 1, new QStandardItem(ThingInfo->GetPlaceName()));
    model->setItem(IndexForAdd, 2, new QStandardItem(ThingInfo->GetThingStatusString()));
    ThingsList.append(ThingInfo);

    ui->ThingsTable->resizeRowToContents(model->rowCount() - 1);

    OrderManipulate::NewAction("Вещь " + ThingInfo->GetThingName() + " зарегистрирована на точку " + ThingInfo->GetPlaceName());
}

void ThingsMenu::SetModelHeader()
{
    model->setHeaderData(0, Qt::Horizontal, "Наименование");
    model->setHeaderData(1, Qt::Horizontal, "Точка ремонта");
    model->setHeaderData(2, Qt::Horizontal, "Статус");
}

void ThingsMenu::RequestToAddThing()
{
    QString ThingName = ui->ThingNameEdit->text();
    QString PlaceName = ui->PlaceComboBox->currentText();
    if (IsThingNameInList(ThingName))
    {
        OrderManipulate::SendErrorMessage("Такое название вещи уже существует.");
        return;
    }
    else
    {
        AddNewThingToModel(new Thing(nullptr, ThingName, PlaceName));
    }
    ClearInputs();
}

void ThingsMenu::UpdatePlaceList(QString PlaceName)
{
    ui->PlaceComboBox->addItem(PlaceName);
}

void ThingsMenu::InfoChanged()
{
    if (not(ui->ThingNameEdit->text().isEmpty()))
    {
        ui->AddThing->setDisabled(false);
    }
    else
    {
        ui->AddThing->setDisabled(true);
    }
}
