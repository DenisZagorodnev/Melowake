#include "alarmlist.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <alarm.h>
int main(int argc, char *argv[])
{


    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);


    AlarmList window;
    window.show();
    return app.exec();
}
