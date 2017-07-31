#include "inventory_window.h"
#include "ui_inventory_window.h"
#include <QDebug>
#include <QTableView>
#include <QtSql/QSqlQueryModel>
#include <QGridLayout>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>

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
    QString databaseLocation = QFileDialog::getOpenFileName(this, tr("Open Database"), "/");

    if(databaseLocation == NULL)
    {
        ui->statusBar->showMessage(tr("Action canceled."));
    }
    else
    {
        QSqlDatabase inventory_DB=QSqlDatabase::addDatabase("QSQLITE");
        inventory_DB.setDatabaseName(databaseLocation);
        if(!inventory_DB.open())
        {
            ui->statusBar->showMessage(tr("Failed to open the database."));
        }
        else
        {
            ui->statusBar->showMessage(tr("Successfully connected to the database."));
            QSqlQueryModel *model = new QSqlQueryModel;
            QSqlQuery *initial_query=new QSqlQuery(inventory_DB);
            initial_query->prepare("SELECT * FROM person");
            initial_query->exec();
            model->setQuery(*initial_query);
            ui->tableView->setModel(model);
        }
    }
}

void inventory_window::on_actionCreate_New_Database_triggered()
{
    QString newDbPath = QFileDialog::getSaveFileName(this, tr("Save New Database"), "/", tr("Database Files (*.db)"));

    qDebug() << newDbPath;

    QSqlDatabase newDatabase=QSqlDatabase::addDatabase("QSQLITE");
    newDatabase.setDatabaseName(newDbPath);
    newDatabase.open();

    QSqlQuery query;
    query.exec("CREATE table person(id integer NOT NULL PRIMARY KEY,firstname varchar(20),lastname varchar(20),active integer);"
               "CREATE table department(id integer NOT NULL PRIMARY KEY,name varchar(20));"
               "CREATE table job_title(id integer NOT NULL PRIMARY KEY,title varchar(30));");
}
