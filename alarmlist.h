#ifndef ALARMLIST_H
#define ALARMLIST_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QDialog>
#include <alarm.h>
#include <QTimer>

namespace Ui {
    class AlarmList;
}

class AlarmList : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmList(QWidget *parent = 0);
    ~AlarmList();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void createActions();
    void createTrayIcon();
    void loadAlarmView(Alarm* alarm);
    void saveAlarmView(Alarm* alarm);
    void loadAlarm(Alarm* alarm);
    void saveAlarm(Alarm* alarm);

private:
    Ui::AlarmList *ui;
    Alarm *alarm;
    QTimer *timer;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void alarmToggle(bool state);
    void onSave();
    void onTimer();
};

#endif // ALARMLIST_H
