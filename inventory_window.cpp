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

}

inventory_window::~inventory_window()
{
    delete ui;
}

void inventory_window::on_actionLoad_Inventory_Database_triggered()
{
    QString databaseLocation = QFileDialog::getOpenFileName(this, tr("Open Database"), ".");
    QSqlDatabase inventory_DB=QSqlDatabase::addDatabase("QSQLITE");
    inventory_DB.setDatabaseName(databaseLocation);
    qDebug()  << inventory_DB;
    if(!inventory_DB.open())
    {
        qDebug()  << inventory_DB.open();
        qDebug()  << inventory_DB.isOpen();
        ui->statusBar->showMessage(tr("Failed to open the database."));
    }
    else
    {
        qDebug()  << inventory_DB.open();
        qDebug()  << inventory_DB.isOpen();
        ui->statusBar->showMessage(tr("Successfully connected to the database."));
    }

    QSqlQueryModel *model = new QSqlQueryModel;

    QSqlQuery *initial_query=new QSqlQuery(inventory_DB);
    initial_query->prepare("SELECT id,name,primary_mac_address,secondary_mac_address,container_id,display_unit_id,config_profile_bag_id,public_key_fingerprint FROM provider_services_host WHERE active=1 AND domain_id=172 AND name LIKE '%sorind%'");
    initial_query->exec();
    model->setQuery(*initial_query);

    ui->tableView->setModel(model);
}
