#ifndef ALARM_H
#define ALARM_H
#include <QVector>

class Alarm
{

public:
    Alarm();
    Alarm(bool enabled, QVector<bool> days, int hour, int minute, int second);
    ~Alarm();

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

    void snooze();
    void dismiss();
    bool isReady();

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

private:
    bool _enabled;
    QVector <bool> _days;
    int _hour;
    int _minute;
    int _second;
    int _delta = 0;
};

#endif // ALARM_H
