#ifndef ALARMWINDOW_H
#define ALARMWINDOW_H

#include <QDialog>

namespace Ui {
    class AlarmWindow;
}

class AlarmWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmWindow(QWidget *parent = nullptr);

signals:

public slots:

private:
    Ui::AlarmWindow *ui;
};

#endif // ALARMWINDOW_H
