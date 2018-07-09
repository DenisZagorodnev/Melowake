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
    _ind = true;
}

Alarm::Alarm(bool enabled, QVector<bool> days, int hour, int minute, int second){
  _days = days;
  _hour = hour;
  _minute = minute;
  _second = second;
  _enabled = enabled;
  _ind = true;
};

Alarm::~Alarm()
{
}

bool Alarm::isDay(){
    QDate date = QDate::currentDate();
    QVector<bool> days1 = days();
    if(days1.at(date.dayOfWeek()-1) == true) return true;
            else return false;


}

bool Alarm::isReady(bool ind) {
    if(ind){
        QTime alarmTime = QTime(hour(), minute(), second());
        alarmTime = alarmTime.addSecs(_delta);
        QTime curTime = QTime::currentTime();
        return ((alarmTime.msecsTo(curTime) > 0)&&(isDay()));
    }
    else return false;
}

void Alarm::snooze() {
    _delta += 10;
}

bool Alarm::dismiss() {
    _delta = 0;
    return false;

}
