#include "alarm.h"
#include <QTime>
#include <QDebug>

Alarm::Alarm()
{
    _days = {false, true, true, true, true, true, true};
    QTime curTime = QTime::currentTime();
    curTime = curTime.addSecs(5);
    setHour(curTime.hour());
    setMinute(curTime.minute());
    setSecond(curTime.second());
    _alarmed = false;
}

Alarm::Alarm(bool enabled, QVector<bool> days, int hour, int minute, int second){
  _days = days;
  _hour = hour;
  _minute = minute;
  _second = second;
  _enabled = enabled;
  _alarmed = false;
};

Alarm::~Alarm()
{
}

bool Alarm::isDay(){
    QDate date = QDate::currentDate();
    QVector<bool> days1 = days();
    if (days1.at(date.dayOfWeek() - 1) == true)
        return true;
    else
        return false;
}

bool Alarm::isReady() {
    if (!enabled())
        return false;
    if (!isDay())
        return false;

    if(!_alarmed){
        QTime alarmTime = QTime(hour(), minute(), second());
        alarmTime = alarmTime.addSecs(_delta);
        QTime curTime = QTime::currentTime();
        int msecs = alarmTime.msecsTo(curTime);
        if ((0 < msecs)&&(msecs < 5000)) {
            _alarmed = true;
            return true;
        }
        return false;
    }
   return false;
}

void Alarm::snooze() {
    _delta += 10;
    _alarmed = false;
}

void Alarm::dismiss() {
    _delta = 0;
    _alarmed = false;

}
