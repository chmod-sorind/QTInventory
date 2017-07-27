#include "inventory_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    inventory_window w;
    w.show();

    return a.exec();
}
