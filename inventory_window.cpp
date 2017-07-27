#include "inventory_window.h"
#include "ui_inventory_window.h"
#include <QDebug>
#include <QTableView>
#include <QtSql/QSqlQueryModel>
#include <QGridLayout>
#include <QString>
#include <QFileDialog>

inventory_window::inventory_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inventory_window)
{
    ui->setupUi(this);



//    QGridLayout* layout = new QGridLayout;
//    QSqlQueryModel *model = new QSqlQueryModel;
//    QTableView *view = new QTableView;

//    model->setHeaderData(0, Qt::Horizontal, tr("a"));
//    model->setHeaderData(1, Qt::Horizontal, tr("b"));
//    model->headerData(0, Qt::Horizontal, tr("ASD"));

//    view->setModel(model);

//    layout->addWidget(view);
//    layout->setAlignment(view,Qt::AlignCenter);
//    setCentralWidget(view);


//    QStringList headers;
//    headers << tr("Header 1") << tr("Header 2") << tr("Header 3") << tr("Heaeder 4");
//    ui->tableWidget->insertColumn(0);
//    ui->tableWidget->insertColumn(1);
//    ui->tableWidget->insertColumn(2);
//    ui->tableWidget->insertColumn(3);
//    ui->tableWidget->setHorizontalHeaderLabels(headers);


}

inventory_window::~inventory_window()
{
    delete ui;
}

void inventory_window::on_actionLoad_Inventory_Database_triggered()
{
//    QString databaseLocation = QFileDialog::getOpenFileName(this, tr("Open Database"), ".");

    QSqlQueryModel *model = new QSqlQueryModel;
//    qDebug() << "Action ! Action !";
//    statusBar()->showMessage(tr("Action !"));

    QSqlDatabase inventory_DB=QSqlDatabase::addDatabase("QSQLITE");
    inventory_DB.setDatabaseName("exampleDB.db");
    qDebug()  << inventory_DB;

    if(!inventory_DB.open())
//        qDebug()  << inventory_DB.open();
//        qDebug()  << inventory_DB.isOpen();
        ui->statusBar->showMessage(tr("Failed to open the database."));
    else
        ui->statusBar->showMessage(tr("Successfully connected to the database."));
}
