#ifndef TIMEALARMCLOCK_H
#define TIMEALARMCLOCK_H
#include <QThread>
#include <QObject>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <QTextStream>
#include <QFile>
#include <linux/input.h>
class TimeAlarmClock : public QThread
{
    Q_OBJECT
public:
    TimeAlarmClock();
private:
    virtual void run();
public:
    uint alarm_clocktime1;
    uint alarm_clocktime2;
    uint alarm_clocktime3;
    uint alarm_clocktime4;
    void beep_on();
    void beep_off();
public slots:
    void closeclock();
};

#endif // TIMEALARMCLOCK_H
