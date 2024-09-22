#ifndef ITEMDIALOD_H
#define ITEMDIALOD_H

#include <QDialog>
#include <QStandardItem>


namespace Ui {
class ItemDialod;
}

class ItemDialod : public QDialog
{
    Q_OBJECT

public:
    QString fio;
    QString phone;
    QString year;
    QString balance;

    explicit ItemDialod(QWidget *parent = nullptr);
    ~ItemDialod();

private slots:
    void on_editFio_textChanged(const QString &arg1);

    void on_editPhone_textChanged(const QString &arg1);

    void on_editYear_textChanged(const QString &arg1);

    void on_editBalance_textChanged(const QString &arg1);

private:
    Ui::ItemDialod *ui;

    void updateOkButtonDisabled();
};

#endif // ITEMDIALOD_H
