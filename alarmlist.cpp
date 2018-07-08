#include "alarmlist.h"
#include "ui_alarmlist.h"
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialog>
#include <alarm.h>
#include <QSettings>
#include <QTimer>

AlarmList::AlarmList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmList),
    alarm(nullptr),
    timer(new QTimer())
{
    ui->setupUi(this);
    ui->onoff->setChecked(false);

    //работа с отдельным будильником!
    alarm = new Alarm(false, {false, false, false, false, false, false, false}, 9, 38);
     onTimer();
    //loadAlarm(alarm);
    //alarm = new Alarm(true, {true, false, true, false, false, true, true}, 10, 42);
    loadAlarmView(alarm);

    createActions();
    createTrayIcon();
    connect(trayIcon, &QSystemTrayIcon::activated, this, &AlarmList::iconActivated);
    connect(ui->onoff, &QCheckBox::toggled, this, &AlarmList::alarmToggle);
    connect(ui->saveButton, &QPushButton::clicked, this, &AlarmList::onSave);
    //loadAlarm(alarm);
    saveAlarm(alarm);
    trayIcon->show();
    setWindowTitle(tr("Melowake"));
    resize(400, 300);
} 

AlarmList::~AlarmList()
{
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
    ui->onoff->setChecked(alarm->getIndicator());

    QVector <bool>week = alarm->getDays();
    ui->day1->setChecked(week.at(0));
    ui->day2->setChecked(week.at(1));
    ui->day3->setChecked(week.at(2));
    ui->day4->setChecked(week.at(3));
    ui->day5->setChecked(week.at(4));
    ui->day6->setChecked(week.at(5));
    ui->day7->setChecked(week.at(6));

    QTime time = QTime(alarm->getHour(), alarm->getMinute(), 0 ,0);
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
    alarm->setIndicator(alarmOn);
}

void AlarmList::onSave()
{
    saveAlarm(alarm);
    hide();
}

void AlarmList::saveAlarm(Alarm* alarm){
    QSettings setting("DenisZagorodnev", "Melowake");
    setting.setValue("hour", alarm->getHour());
    setting.setValue("minute", alarm->getMinute());
    setting.setValue("indicator", alarm->getIndicator());

    setting.setValue("monday", alarm->getDays()[0]);
    setting.setValue("tuesday", alarm->getDays()[1]);
    setting.setValue("wednesday", alarm->getDays()[2]);
    setting.setValue("thursday", alarm->getDays()[3]);
    setting.setValue("friday", alarm->getDays()[4]);
    setting.setValue("saturday", alarm->getDays()[5]);
    setting.setValue("sunday", alarm->getDays()[6]);


}

void AlarmList::onTimer(){
    timer->singleShot(1000, this, &AlarmList::onTimer);
    QTime cur = QTime::currentTime();
    if((alarm->getHour() == cur.hour())&&(alarm->getMinute() == cur.minute())&&(cur.second()==1)){
        QMessageBox::information(0, "information", "It is an alert");
    }
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

    bool indicator=setting.value("indicator",false).toBool();

    alarm->setDays(days);
    alarm->setHour(hour);
    alarm->setMinute(minute);
    alarm->setIndicator(indicator);

   // loadAlarmView(alarm);
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
