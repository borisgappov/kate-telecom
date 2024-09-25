#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QStandardItemModel>
#include <QFile>
#include <QFileInfo>
#include "proxymodel.h"

QT_BEGIN_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT

public:
    static const QString dataFile;
    static const QString lineTemplate;

    DataSource();
    ~DataSource();

    ProxyModel * GetModel();

    void Load();

    void Save();

    void Seed();

    void DeleteRow(QModelIndexList indexes);

    void AddRow(QString fio, QString phone, QString year, QString balance);

    void filterByYear(QString year);

    void filterByName(QString name);

    void showNegativeOnly(bool negativeOnly);

Q_SIGNAL
    void rowsCountChanged();

private:
    QStandardItemModel * model;
    ProxyModel * proxyModel;

    bool skipSave;

    void InitializeModel();

    QFile * OpenFile(bool overwrite = false);
};

QT_END_NAMESPACE

#endif // DATASOURCE_H

