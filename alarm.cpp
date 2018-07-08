#include "alarm.h"
#include <QTime>
#include <QDebug>

Alarm::Alarm()
{
    _days = {true, true, true, true, true, true, true};
    QTime curTime = QTime::currentTime();
    curTime = curTime.addSecs(5);
    setHour(curTime.hour());
    setMinute(curTime.minute());
    setSecond(curTime.second());
}

Alarm::Alarm(bool enabled, QVector<bool> days, int hour, int minute, int second){
  _days = days;
  _hour = hour;
  _minute = minute;
  _second = second;
  _enabled = enabled;
};

Alarm::~Alarm()
{
}

bool Alarm::isReady() {
   QTime alarmTime = QTime(hour(), minute(), second());
   alarmTime = alarmTime.addSecs(_delta);
   QTime curTime = QTime::currentTime();
   return alarmTime.msecsTo(curTime) > 0;
}

void Alarm::snooze() {
    _delta += 15;
}

void Alarm::dismiss() {
    _delta = 0;
}
