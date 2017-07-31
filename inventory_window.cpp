#include "inventory_window.h"
#include "ui_inventory_window.h"
#include <QDebug>
#include <QTableView>
#include <QtSql/QSqlQueryModel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

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
    dbPath = QFileDialog::getOpenFileName(this, tr("Open Database"), "/");

    if(dbPath == NULL)
    {
        ui->statusBar->showMessage(tr("Action canceled."));
    }
    else
    {
        inventoryDB=QSqlDatabase::addDatabase("QSQLITE");
        inventoryDB.setDatabaseName(dbPath);
        if(!inventoryDB.open())
        {
            ui->statusBar->showMessage(tr("Failed to open the database ") + dbPath);
        }
        else
        {
            tableViewModel=new QSqlQueryModel;
            loadInventoryDB=new QSqlQuery(inventoryDB);
            loadInventoryDB->prepare("SELECT * FROM person");
            loadInventoryDB->exec();
            tableViewModel->setQuery(*loadInventoryDB);
            ui->tableView->setModel(tableViewModel);
            ui->statusBar->showMessage(tr("Successfully connected to the database: ") + dbPath);
        }
    }
}

void inventory_window::on_actionCreate_New_Database_triggered()
{
    dbPath = QFileDialog::getSaveFileName(this, tr("Save New Database"), "/", tr("Database Files (*.db)"));
    if(dbPath == NULL)
    {
        ui->statusBar->showMessage(tr("Action canceled."));
    }
    else
    {
        inventoryDB=QSqlDatabase::addDatabase("QSQLITE");
        inventoryDB.setDatabaseName(dbPath);
        inventoryDB.open();

        QSqlQuery *createPersonTable=new QSqlQuery(inventoryDB);
        QSqlQuery *createDepartmentTable=new QSqlQuery(inventoryDB);
        QSqlQuery *createJob_titleTable=new QSqlQuery(inventoryDB);

        createPersonTable->prepare("CREATE table person(id integer NOT NULL PRIMARY KEY,firstname varchar(20),lastname varchar(20),active integer)");
        createPersonTable->exec();
        createDepartmentTable->prepare("CREATE table department(id integer NOT NULL PRIMARY KEY,name varchar(20));");
        createDepartmentTable->exec();
        createJob_titleTable->prepare("CREATE table job_title(id integer NOT NULL PRIMARY KEY,title varchar(30));");
        createJob_titleTable->exec();

        tableViewModel = new QSqlQueryModel;
        loadInventoryDB=new QSqlQuery(inventoryDB);
        loadInventoryDB->prepare("SELECT * FROM person");
        loadInventoryDB->exec();
        tableViewModel->setQuery(*loadInventoryDB);
        ui->tableView->setModel(tableViewModel);
        ui->statusBar->showMessage(tr("Successfully connected to the database: ") + dbPath);
    }

}

void inventory_window::on_pushButton_clicked()
{
    if(!inventoryDB.open())
    {
       ui->statusBar->showMessage(tr("No DB Connection."));
    }
    else
    {
        QSqlQuery *insertIntoPersonTable=new QSqlQuery(inventoryDB);
        insertIntoPersonTable->prepare("INSERT INTO person (firstname, lastname, active) VALUES (:firstname, :lastname, :active)");
        insertIntoPersonTable->bindValue(":firstname", ui->firstNameLineEdit->text());
        insertIntoPersonTable->bindValue(":lastname",ui->lastNameLineEdit->text());
        insertIntoPersonTable->bindValue(":active", 1);
        insertIntoPersonTable->exec();
        loadInventoryDB=new QSqlQuery(inventoryDB);
        loadInventoryDB->prepare("SELECT * FROM person");
        loadInventoryDB->exec();
        tableViewModel->setQuery(*loadInventoryDB);
        ui->tableView->setModel(tableViewModel);

    }
}
