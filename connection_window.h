#ifndef CONNECTION_WINDOW_H
#define CONNECTION_WINDOW_H

#include <QMainWindow>

namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectionWindow(QWidget *parent = 0);
    ~ConnectionWindow();

private:
    Ui::ConnectionWindow *ui;
};

#endif // CONNECTION_WINDOW_H
