#include "inventory_window.h"
#include "ui_inventory_window.h"
#include <QDebug>
#include <QTableView>
#include <QtSql/QSqlQueryModel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>

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

QString inventory_window::get_time_now()
{
    QDateTime t1(QDateTime::currentDateTime());
    QString t2 = t1.toString("yyyy-MM-dd hh:mm:ss");
    return t2;
}

void inventory_window::clear_HwLIneEdit()
{
    ui->hwAsigneeLineEdit->clear();
    ui->hwPrimaryMacLineEdit->clear();
    ui->hwTypeLineEdit->clear();
}

void inventory_window::clear_PersonLIneEdit()
{
    ui->firstNameLineEdit->clear();
    ui->lastNameLineEdit->clear();
    ui->departmentLineEdit->clear();
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
            personTableViewModel=new QSqlQueryModel;
            hardwareTableViewModel=new QSqlQueryModel;

            loadInventoryDB_person=new QSqlQuery(inventoryDB);
            loadInventoryDB_person->prepare("SELECT * FROM person");
            loadInventoryDB_person->exec();
            qDebug() << "Load Person Table Errors: " << loadInventoryDB_person->lastError();
            personTableViewModel->setQuery(*loadInventoryDB_person);
            ui->tableViewPerson->setModel(personTableViewModel);

            loadInventoryDB_hardware=new QSqlQuery(inventoryDB);
            loadInventoryDB_hardware->prepare("SELECT hw.type as Type,"
                                              "hw.primary_mac_address as 'MAC Address',"
                                              "hw.last_modified as 'Update Time',"
                                              "hw.current_user_fullname as Assignee FROM hardware as hw");
            loadInventoryDB_hardware->exec();
            qDebug() << "Load Hardware Table Errors: " << loadInventoryDB_hardware->lastError();
            hardwareTableViewModel->setQuery(*loadInventoryDB_hardware);
            ui->tableViewHardware->setModel(hardwareTableViewModel);


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
        QSqlQuery *createHardwareTable=new QSqlQuery(inventoryDB);


        createPersonTable->prepare("CREATE TABLE person(id INTEGER NOT NULL PRIMARY KEY,"
                                   "firstname VARCHAR(20),"
                                   "lastname VARCHAR(20),"
                                   "department VARCHAR(20),"
                                   "active BOOLEAN)");
        createHardwareTable->prepare("CREATE TABLE hardware(id INTEGER NOT NULL PRIMARY KEY,"
                                     "type VARCHAR(20),"
                                     "primary_mac_address VARCHAR(20),"
                                     "active BOOLEAN,"
                                     "last_modified CURRENT_TIMESTAMP,"
                                     "current_user_fullname VARCHAR(50),"
                                     "current_user_id,"
                                     "FOREIGN KEY(current_user_id) REFERENCES person(id))");
        createPersonTable->exec();
        qDebug() << "Create Person Table Errors: " << createPersonTable->lastError();

        createHardwareTable->exec();
        qDebug() << "Create Hardware Table Errors: " << createHardwareTable->lastError();


        personTableViewModel=new QSqlQueryModel;
        hardwareTableViewModel=new QSqlQueryModel;

        loadInventoryDB_person=new QSqlQuery(inventoryDB);
        loadInventoryDB_person->prepare("SELECT * FROM person");
        loadInventoryDB_person->exec();
        qDebug() << "Load Person Table Errors: " << loadInventoryDB_person->lastError();
        personTableViewModel->setQuery(*loadInventoryDB_person);
        ui->tableViewPerson->setModel(personTableViewModel);

        loadInventoryDB_hardware=new QSqlQuery(inventoryDB);
        loadInventoryDB_hardware->prepare("SELECT hw.type as Type,"
                                          "hw.primary_mac_address as 'MAC Address',"
                                          "hw.last_modified as 'Update Time',"
                                          "hw.current_user_fullname as Assignee FROM hardware as hw");
        loadInventoryDB_hardware->exec();
        qDebug() << "Load Hardware Table Errors: " << loadInventoryDB_hardware->lastError();
        hardwareTableViewModel->setQuery(*loadInventoryDB_hardware);
        ui->tableViewHardware->setModel(hardwareTableViewModel);
    }

}

void inventory_window::on_pushButtonCreatePerson_clicked()
{
    if(!inventoryDB.open())
    {
       ui->statusBar->showMessage(tr("No DB Connection."));
    }
    else
    {
        QSqlQuery *insertIntoPersonTable=new QSqlQuery(inventoryDB);
        insertIntoPersonTable->prepare("INSERT INTO person (firstname, lastname, department, active) VALUES (:firstname, :lastname, :department, :active)");
        insertIntoPersonTable->bindValue(":firstname", ui->firstNameLineEdit->text());
        insertIntoPersonTable->bindValue(":lastname",ui->lastNameLineEdit->text());
        insertIntoPersonTable->bindValue(":department",ui->departmentLineEdit->text());
        insertIntoPersonTable->bindValue(":active", 1);
        insertIntoPersonTable->exec();
        qDebug() << "Insert Into Person Table Errors: " << insertIntoPersonTable->lastError();

        personTableViewModel=new QSqlQueryModel;
        hardwareTableViewModel=new QSqlQueryModel;

        loadInventoryDB_person=new QSqlQuery(inventoryDB);
        loadInventoryDB_person->prepare("SELECT * FROM person");
        loadInventoryDB_person->exec();
        qDebug() << "Load Person Table Errors: " << loadInventoryDB_person->lastError();
        personTableViewModel->setQuery(*loadInventoryDB_person);
        ui->tableViewPerson->setModel(personTableViewModel);

        loadInventoryDB_hardware=new QSqlQuery(inventoryDB);
        loadInventoryDB_hardware->prepare("SELECT hw.type as Type,"
                                          "hw.primary_mac_address as 'MAC Address',"
                                          "hw.last_modified as 'Update Time',"
                                          "hw.current_user_fullname as Assignee FROM hardware as hw");
        loadInventoryDB_hardware->exec();
        qDebug() << "Load Hardware Table Errors: " << loadInventoryDB_hardware->lastError();
        hardwareTableViewModel->setQuery(*loadInventoryDB_hardware);
        ui->tableViewHardware->setModel(hardwareTableViewModel);
        clear_PersonLIneEdit();
    }
}
void inventory_window::on_pushButtonCreateHardware_clicked()
{
    if(!inventoryDB.open())
    {
       ui->statusBar->showMessage(tr("No DB Connection."));
    }
    else
    {
        QSqlQuery *insertIntoPersonTable=new QSqlQuery(inventoryDB);
        insertIntoPersonTable->prepare("INSERT INTO hardware (type, primary_mac_address, active, last_modified, current_user_fullname)"
                                       "VALUES (:type, :primary_mac_address, :active, :last_modified, :current_user_fullname)");
        insertIntoPersonTable->bindValue(":type", ui->hwTypeLineEdit->text());
        insertIntoPersonTable->bindValue(":primary_mac_address",ui->hwPrimaryMacLineEdit->text());
        insertIntoPersonTable->bindValue(":active", 1);
        insertIntoPersonTable->bindValue(":last_modified", get_time_now());
        insertIntoPersonTable->bindValue(":current_user_fullname",ui->hwAsigneeLineEdit->text());
        insertIntoPersonTable->exec();
        qDebug() << "Insert Into Person Table Errors: " << insertIntoPersonTable->lastError();

        personTableViewModel=new QSqlQueryModel;
        hardwareTableViewModel=new QSqlQueryModel;

        loadInventoryDB_person=new QSqlQuery(inventoryDB);
        loadInventoryDB_person->prepare("SELECT * FROM person");
        loadInventoryDB_person->exec();
        qDebug() << "Load Person Table Errors: " << loadInventoryDB_person->lastError();
        personTableViewModel->setQuery(*loadInventoryDB_person);
        ui->tableViewPerson->setModel(personTableViewModel);

        loadInventoryDB_hardware=new QSqlQuery(inventoryDB);
        loadInventoryDB_hardware->prepare("SELECT hw.type as Type,"
                                          "hw.primary_mac_address as 'MAC Address',"
                                          "hw.last_modified as 'Update Time',"
                                          "hw.current_user_fullname as Assignee FROM hardware as hw");
        loadInventoryDB_hardware->exec();
        qDebug() << "Load Hardware Table Errors: " << loadInventoryDB_hardware->lastError();
        hardwareTableViewModel->setQuery(*loadInventoryDB_hardware);
        ui->tableViewHardware->setModel(hardwareTableViewModel);
        clear_HwLIneEdit();
    }
}
