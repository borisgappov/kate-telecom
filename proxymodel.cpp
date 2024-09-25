#include "proxymodel.h"

ProxyModel::ProxyModel(QObject* parent): QSortFilterProxyModel(parent)
{
}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {

    QModelIndex nameIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex yearIndex = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex balanceIndex = sourceModel()->index(sourceRow, 3, sourceParent);

    QString name = sourceModel()->data(nameIndex).toString();
    QString year = sourceModel()->data(yearIndex).toString();
    QString balance = sourceModel()->data(balanceIndex).toString();

    float balanceFloat = balance.toFloat();

    return (filterYear.isEmpty() ? true : year == filterYear)
           && (filterName.isEmpty() ? true : name.contains(filterName))
           && (negativeBalanceOnly ? balanceFloat < 0 : true);
}

void ProxyModel::setYearFilter(QString filterYear){
    this->filterYear = filterYear;
    invalidateFilter();
}

void ProxyModel::setNameFilter(QString filterName){
    this->filterName = filterName;
    invalidateFilter();
}

void ProxyModel::setNegativeBalanceOnly(bool negativeBalanceOnly){
    this->negativeBalanceOnly = negativeBalanceOnly;
    invalidateFilter();
}
