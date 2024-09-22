#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QStandardItemModel>
#include <QFile>
#include <QFileInfo>

class DataSource
{   
public:
    static const QString dataFile;
    static const QString lineTemplate;

    DataSource();
    ~DataSource();

    QStandardItemModel * GetModel();

    void Load();

    void Save();

    void Seed();

    void DeleteRow(QModelIndexList indexes);

    void AddRow(QString fio, QString phone, QString year, QString balance);

private:
    QStandardItemModel * model;

    bool skipSave;

    void InitializeModel();

    QFile * OpenFile(bool overwrite = false);
};

#endif // DATASOURCE_H
