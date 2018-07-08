#ifndef ALARM_H
#define ALARM_H
#include <QVector>

class Alarm
{

public:
    Alarm(bool indicator, QVector <bool> days, int hour, int minute){
      this->Days = days;
      this->Hour = hour;
      this->Minute = minute;
      this->Indicator = indicator;
    };

    ~Alarm();

    void setDays(QVector <bool> days){
        this->Days = days;
    }
    void setHour(int hour){
        this->Hour = hour;
    }
    void setMinute(int minute){
        this->Minute = minute;
    }
    void setIndicator(bool indicator){
        this->Indicator = indicator;
    }

    QVector<bool> getDays(){
        return(this->Days);
    }
    int getHour(){
        return(this->Hour);
    }
    int getMinute(){
        return(this->Minute);
    }
    bool getIndicator(){
        return(this->Indicator);
    }

private:
    bool Indicator;
    QVector <bool> Days;
    int Hour;
    int Minute;
};






#endif // ALARM_H
