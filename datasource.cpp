#include <QMessageBox>
#include <QStringList>

#include "datasource.h"

const QString DataSource::dataFile = "phones.txt";
const QString DataSource::lineTemplate = QString("%1\t%2\t%3\t%4\n");

DataSource::DataSource() {
    InitializeModel();
    Load();
}

DataSource::~DataSource() {
    delete model;
}

QStandardItemModel * DataSource::GetModel(){
    return model;
}

void DataSource::InitializeModel()
{
    model = new QStandardItemModel();

    QStringList *columns = new QStringList();
    columns->append("ФИО");
    columns->append("Номер телефона");
    columns->append("Год подключения");
    columns->append("Баланс");

    model->setHorizontalHeaderLabels(*columns);
}

void DataSource::Load() {
    skipSave = true;

    if(!QFileInfo::exists(dataFile)) {
        Seed();
    }

    model->setRowCount(0);

    QFile * file = OpenFile();

    int rowIndex = 0;
    QTextStream in(file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("\t");

        for(int colIndex = 0; colIndex < fields.count(); colIndex++) {
            model->setItem(rowIndex, colIndex, new QStandardItem(fields[colIndex]));
        }

        rowIndex++;
    }

    file->close();
    delete file;

    skipSave = false;
}

void DataSource::Save() {

    if(skipSave)
        return;

    QFile * file = OpenFile(true);

    for(int rowIndex = 0; rowIndex < model->rowCount(); rowIndex++) {
        QString line = "";
        int lastColIndex = model->columnCount() - 1;
        for(int colIndex = 0; colIndex <= lastColIndex; colIndex++) {
            QStandardItem * item = model->item(rowIndex, colIndex);
            line += item->text() + (colIndex == lastColIndex ? "\n" : "\t");
        }

        file->write(line.toUtf8());
    }

    file->close();
    delete file;
}

void DataSource::Seed(){
    QFile * file = OpenFile(true);

    file->write(lineTemplate.arg("Иванов А.С.", "+79235672930", "2002", "550").toUtf8());
    file->write(lineTemplate.arg("Петрова К.Д.", "+79528472748", "2018", "100").toUtf8());
    file->write(lineTemplate.arg("Селезнев К.Е.", "+79352525423", "2021", "-350").toUtf8());
    file->write(lineTemplate.arg("Сидорова П.С.", "+79536622323", "2011", "231").toUtf8());
    file->write(lineTemplate.arg("Васильев Л.Н.", "+79955646367", "2012", "-1107").toUtf8());

    file->close();
    delete file;
}

void DataSource::DeleteRow(QModelIndexList indexes)
{
    while (!indexes.isEmpty())
    {
        model->removeRows(indexes.last().row(), 1);
        indexes.removeLast();
    }
    Save();
}

void DataSource::AddRow(QString fio, QString phone, QString year, QString balance)
{
    QList<QStandardItem*> row;
    row.append(new QStandardItem(fio));
    row.append(new QStandardItem(phone));
    row.append(new QStandardItem(year));
    row.append(new QStandardItem(balance));
    model->appendRow(row);
    Save();
}

QFile * DataSource::OpenFile(bool overwrite) {
    QFile * file = new QFile(dataFile);

    if(!file->open(overwrite ? QIODevice::ReadWrite | QIODevice::Truncate : QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file->errorString());
    }

    return file;
}

