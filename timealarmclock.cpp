#include "timealarmclock.h"
#include <QDateTime>
#include <QDebug>
TimeAlarmClock::TimeAlarmClock()
{

}
void TimeAlarmClock::run()
{
    while (1) {
        QDateTime time = QDateTime::currentDateTime();   //获取当前时间
        uint timeT = time.toTime_t();   //将当前时间转为时间戳
//        qDebug()<<timeT<<alarm_clocktime1;
        if(alarm_clocktime1==timeT){
            beep_on();
//            qDebug()<<"open";
        }else{

        }
        if(alarm_clocktime2==timeT){
            beep_on();
        }else{

        }
        if(alarm_clocktime3==timeT){
            beep_on();
        }else{

        }
        if(alarm_clocktime4==timeT){
            beep_on();
        }else{

        }
    }
}
void TimeAlarmClock::closeclock(){
    beep_off();
}
void TimeAlarmClock::beep_on()
{
    int fd;
    struct input_event event;
    struct timeval time;
    fd = open("/dev/input/by-path/platform-beeper-event", O_RDWR);
    event.type = EV_SND;
    event.code = SND_TONE;
    event.value = 1000;
    time.tv_sec = 1;
    time.tv_usec = 0;
    event.time = time;
    write(fd, &event, sizeof(struct input_event));
    close(fd);
}
void TimeAlarmClock::beep_off()
{
    int fd;
    struct input_event event;
    struct timeval time;
    fd = open("/dev/input/by-path/platform-beeper-event", O_RDWR);
    event.type = EV_SND;
    event.code = SND_TONE;
    event.value = 0;
    time.tv_sec = 0;
    time.tv_usec = 0;
    event.time = time;
    write(fd, &event, sizeof(struct input_event));
    close(fd);
}


