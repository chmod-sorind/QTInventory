#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QtSql/QSqlQueryModel>
#include <QString>
#include <QDateTime>

namespace Ui {
class inventory_window;
}

class inventory_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit inventory_window(QWidget *parent = 0);
    ~inventory_window();
    void clear_PersonLIneEdit();
    void clear_HwLIneEdit();
    QString get_time_now();

private slots:
    void on_actionLoad_Inventory_Database_triggered();

    void on_actionCreate_New_Database_triggered();

    void on_pushButtonCreateHardware_clicked();

    void on_pushButtonCreatePerson_clicked();

private:
    Ui::inventory_window *ui;
    QSqlDatabase inventoryDB;
    QSqlQueryModel *personTableViewModel;
    QSqlQueryModel *hardwareTableViewModel;
    QSqlQuery *loadInventoryDB_person;
    QSqlQuery *loadInventoryDB_hardware;
    QString dbPath;
};

#endif // INVENTORY_WINDOW_H
