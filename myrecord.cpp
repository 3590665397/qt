#include "myrecord.h"
#include "myrecordc.h"
#include <QTimer>
myrecord::myrecord()
{
    flag = 1;
}

void myrecord::myslotflag()
{
    flag = !flag;// 切换标志位的值（取反）
    //qDebug() << flag <<"end";
}

void myrecord::run()
{
    func_record();
    emit mysignal();
}
