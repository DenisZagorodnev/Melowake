#include "alarmlist.h"
#include "ui_alarmlist.h"
#include <QCloseEvent>
#include <QSettings>
#include <QTimer>
#include <QDebug>
#include <QWebEngineView>
#include <QtWidgets>

#include "alarmwindow.h"

AlarmList::AlarmList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmList),
    alarm(new Alarm()),
    timer(new QTimer())
{
    ui->setupUi(this);
    ui->onoff->setChecked(false);

    alarm = new Alarm(false, {false,false,false,false,false,false,false }, 0,0,1);
    loadAlarm(alarm);
    loadAlarmView(alarm);

    createActions();
    createTrayIcon();
    connect(trayIcon, &QSystemTrayIcon::activated, this, &AlarmList::iconActivated);
    connect(ui->onoff, &QCheckBox::toggled, this, &AlarmList::alarmToggle);
    connect(ui->saveButton, &QPushButton::clicked, this, &AlarmList::onSave);

    trayIcon->show();
    setWindowTitle(tr("Melowake"));
    resize(400, 300);
    onTimer();
}

AlarmList::~AlarmList()
{
    delete timer;
    delete alarm;
    delete ui;
}

void AlarmList::alarmToggle(bool state)
{
    ui->timeEdit->setEnabled(state);
    ui->daysGroup->setEnabled(state);
}

//отображение параметров будильника на экране
void AlarmList::loadAlarmView(Alarm* alarm)
{
    ui->onoff->setChecked(alarm->enabled());
    alarmToggle(alarm->enabled());
    QVector <bool>week = alarm->days();
    ui->day1->setChecked(week.at(0));
    ui->day2->setChecked(week.at(1));
    ui->day3->setChecked(week.at(2));
    ui->day4->setChecked(week.at(3));
    ui->day5->setChecked(week.at(4));
    ui->day6->setChecked(week.at(5));
    ui->day7->setChecked(week.at(6));

    QTime time = QTime(alarm->hour(), alarm->minute(), alarm->second());
    ui->timeEdit->setTime(time);
}

void AlarmList::saveAlarmView(Alarm* alarm)
{
    QTime time = ui->timeEdit->time();
    int hour = time.hour();
    int min = time.minute();

    bool alarmOn = ui->onoff->isChecked();
    QVector<bool> days;
    bool d1 = ui->day1->isChecked();
    days.append(d1);
    bool d2 = ui->day2->isChecked();
    days.append(d2);
    bool d3 = ui->day3->isChecked();
    days.append(d3);
    bool d4 = ui->day4->isChecked();
    days.append(d4);
    bool d5 = ui->day5->isChecked();
    days.append(d5);
    bool d6 = ui->day6->isChecked();
    days.append(d6);
    bool d7 = ui->day7->isChecked();
    days.append(d7);

    alarm->setDays(days);
    alarm->setHour(hour);
    alarm->setMinute(min);
    alarm->setEnabled(alarmOn);
}

void AlarmList::onSave()
{
    saveAlarmView(alarm);
    saveAlarm(alarm);
    hide();
}

void AlarmList::saveAlarm(Alarm* alarm){
    QSettings setting("DenisZagorodnev", "Melowake");
    setting.setValue("hour", alarm->hour());
    setting.setValue("minute", alarm->minute());
    setting.setValue("enabled", alarm->enabled());

    setting.setValue("monday", alarm->days()[0]);
    setting.setValue("tuesday", alarm->days()[1]);
    setting.setValue("wednesday", alarm->days()[2]);
    setting.setValue("thursday", alarm->days()[3]);
    setting.setValue("friday", alarm->days()[4]);
    setting.setValue("saturday", alarm->days()[5]);
    setting.setValue("sunday", alarm->days()[6]);
}


MainWindow::MainWindow()
{
    QUrl url;
    url = QUrl("https://w.soundcloud.com/player/?visual=true&url=https%3A%2F%2Fapi.soundcloud.com%2Ftracks%2F293&show_artwork=true&auto_play=true");
    setAttribute(Qt::WA_DeleteOnClose, true);
    view = new QWebEngineView(this);
    view->load(url);
    setCentralWidget(view);
}




void AlarmList::onTimer()
{
    if (alarm->isReady()) {
        AlarmWindow wind;


        MainWindow *wid = new MainWindow();
        wid->setVisible(false);
        ui->gridLayout->addWidget(wid);



        if (wind.exec() == QDialog::Rejected) {
            alarm->snooze();
            wid->setEnabled(false);
            delete(wid);
        } else{
            alarm->dismiss();
            wid->setEnabled(false);
            delete(wid);
        }
    }
    timer->singleShot(1000, this, &AlarmList::onTimer);
}




void AlarmList::loadAlarm(Alarm* alarm){
    QSettings setting("DenisZagorodnev", "Melowake");
    int hour = setting.value("hour", 10).toInt();
    int minute = setting.value("minute",10).toInt();
    QVector <bool> days;

    days.append(setting.value("monday", false).toBool());
    days.append(setting.value("tuesday", false).toBool());
    days.append(setting.value("wednesday", false).toBool());
    days.append(setting.value("thursday", false).toBool());
    days.append(setting.value("friday", false).toBool());
    days.append(setting.value("saturday", false).toBool());
    days.append(setting.value("sunday", false).toBool());
    bool enabled = setting.value("enabled",false).toBool();

    alarm->setDays(days);
    alarm->setHour(hour);
    alarm->setMinute(minute);
    alarm->setEnabled(enabled);
}


void AlarmList::closeEvent(QCloseEvent *event)
{
 #ifdef Q_OS_OSX
     if (!event->spontaneous() || !isVisible()) {
         return;
     }
 #endif
     if (trayIcon->isVisible()) {
         hide();
         event->ignore();
     }
}


 void AlarmList::iconActivated(QSystemTrayIcon::ActivationReason reason)
 {
     switch (reason) {
     case QSystemTrayIcon::Trigger:
     case QSystemTrayIcon::MiddleClick:
         break;
     default:
         ;
     }
 }


 void AlarmList::createActions()
 {
     restoreAction = new QAction(tr("&Restore"), this);
     connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

     quitAction = new QAction(tr("&Quit"), this);
     connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
 }


 void AlarmList::createTrayIcon()
 {
     trayIconMenu = new QMenu(this);
     trayIconMenu->addAction(restoreAction);
     trayIconMenu->addSeparator();
     trayIconMenu->addAction(quitAction);

     trayIcon = new QSystemTrayIcon(this);
     trayIcon->setContextMenu(trayIconMenu);
     QIcon icon = QIcon(":/icons/picture1.png");
     trayIcon->setIcon(icon);
 }
