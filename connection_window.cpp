#include "connection_window.h"
#include "ui_connection_window.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionWindow)
{
    ui->setupUi(this);
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}
