#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
private:
    QString filterYear;
    QString filterName;
    bool negativeBalanceOnly;

public:
    explicit ProxyModel(QObject* parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

public slots:
    void setYearFilter(QString regExp);
    void setNameFilter(QString filterName);
    void setNegativeBalanceOnly(bool negativeBalanceOnly);
};

#endif // PROXYMODEL_H
