#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QStandardItemModel>
#include <QFile>
#include <QMessageBox>
#include <QFileInfo>
#include "itemdialod.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataSource = new DataSource();

    ui->tableView->setModel(dataSource->GetModel());

    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->setColumnWidth(2, 120);
    ui->tableView->setColumnWidth(3, 120);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::selectionChanged);
    connect(dataSource->GetModel(), &QStandardItemModel::dataChanged, this, &MainWindow::dataChanged);
    connect(dataSource, &DataSource::rowsCountChanged, this, &MainWindow::updateRoesCount);

    updateRoesCount();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dataSource;
}

void MainWindow::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
    ui->buttonDel->setDisabled(selected.isEmpty());
}

void MainWindow::on_buttonDel_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    dataSource->DeleteRow(indexes);
}


void MainWindow::on_buttonAdd_clicked()
{
    ItemDialod dialog;
    if(dialog.exec() == QDialog::Accepted)
    {
        dataSource->AddRow(dialog.fio, dialog.phone, dialog.year, dialog.balance);
    }
}

void MainWindow::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
{
    dataSource->Save();
}

void MainWindow::on_buttonReset_clicked()
{
    dataSource->Seed();
    dataSource->Load();
    updateRoesCount();
}

void MainWindow::on_fioFilterButton_clicked()
{
    dataSource->filterByName(ui->fioFilterEdit->text());
}

void MainWindow::on_yearFilterButton_clicked()
{
    dataSource->filterByYear(ui->yearFilterEdit->text());
}

void MainWindow::on_negativeFilterButton_clicked()
{
    dataSource->showNegativeOnly(true);
}

void MainWindow::on_clearFilterButton_clicked()
{
    dataSource->filterByName("");
    dataSource->filterByYear("");
    dataSource->showNegativeOnly(false);
    ui->fioFilterEdit->setText("");
    ui->yearFilterEdit->setText("");
}

void MainWindow::updateRoesCount(){
    ui->recordsCountEdit->setText(QString("%1").arg(dataSource->GetModel()->rowCount()));
}
