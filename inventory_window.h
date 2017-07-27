#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <QMainWindow>

namespace Ui {
class inventory_window;
}

class inventory_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit inventory_window(QWidget *parent = 0);
    ~inventory_window();

private:
    Ui::inventory_window *ui;
};

#endif // INVENTORY_WINDOW_H
