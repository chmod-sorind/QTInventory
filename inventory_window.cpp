#include "inventory_window.h"
#include "ui_inventory_window.h"

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
