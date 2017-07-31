#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class inventory_window;
}

class inventory_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit inventory_window(QWidget *parent = 0);
    ~inventory_window();

private slots:
    void on_actionLoad_Inventory_Database_triggered();

    void on_actionCreate_New_Database_triggered();

private:
    Ui::inventory_window *ui;
};

#endif // INVENTORY_WINDOW_H
