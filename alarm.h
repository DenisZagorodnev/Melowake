#ifndef ALARM_H
#define ALARM_H
#include <QVector>
#include <QTime>

class Alarm
{

public:

    Alarm();
    Alarm(bool enabled, QVector<bool> days, int hour, int minute, int second);
    ~Alarm();

    bool _alarmed = false;

    void setDays(QVector <bool> days){
        _days = days;
    }
    void setHour(int hour){
        _hour = hour;
    }
    void setMinute(int minute){
        _minute = minute;
    }
    void setSecond(int second){
        _second = second;
    }

    void setEnabled(bool enebaled){
        _enabled = enebaled;
    }

    void setAlarmtime(QTime cur){
        _alarmTime = cur;
    }

    void snooze();
    void dismiss();
    bool isReady();
    bool isDay();

    QVector<bool> days() const {
        return _days;
    }

    int hour() const {
        return _hour;
    }

    int minute() {
        return _minute;
    }

    bool enabled() {
        return _enabled;
    }

    int second(){
        return _second;
    }

    int delta(){
        return _delta;
    }

private:
    bool _enabled;
    QVector <bool> _days;
    int _hour;
    int _minute;
    int _second;
    int _delta = 0;

    QTime _alarmTime = QTime::currentTime();
};

#endif // ALARM_H
