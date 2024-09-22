#include "itemdialod.h"
#include "ui_itemdialod.h"

ItemDialod::ItemDialod(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemDialod)
{
    ui->setupUi(this);
    updateOkButtonDisabled();
}

ItemDialod::~ItemDialod()
{
    delete ui;
}

void ItemDialod::on_editFio_textChanged(const QString &arg1)
{
    fio = arg1;
    updateOkButtonDisabled();
}


void ItemDialod::on_editPhone_textChanged(const QString &arg1)
{
    phone = arg1;
    updateOkButtonDisabled();
}


void ItemDialod::on_editYear_textChanged(const QString &arg1)
{
    year = arg1;
    updateOkButtonDisabled();
}


void ItemDialod::on_editBalance_textChanged(const QString &arg1)
{
    balance = arg1;
    updateOkButtonDisabled();
}

void ItemDialod::updateOkButtonDisabled() {
    bool disabled = ui->editFio->text().isEmpty()
                    || ui->editPhone->text().isEmpty()
                    || ui->editYear->text().isEmpty()
                    || ui->editBalance->text().isEmpty();

    ui->buttonBox->buttons().first()->setDisabled(disabled);
}
