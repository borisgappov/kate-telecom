#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelection>

#include "datasource.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles = QList<int>());
    void updateRoesCount();

private slots:
    void on_buttonDel_clicked();

    void on_buttonAdd_clicked();

    void on_buttonReset_clicked();

    void on_fioFilterButton_clicked();

    void on_clearFilterButton_clicked();

    void on_yearFilterButton_clicked();

    void on_negativeFilterButton_clicked();

private:
    Ui::MainWindow *ui;
    DataSource * dataSource;
};
#endif // MAINWINDOW_H
