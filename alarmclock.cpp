#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::loc_time_init()
{
    currentTime=new QTimer(this);
    currentTime->start(1000); // 每次发射timeout信号时间间隔为1秒
    connect(currentTime,SIGNAL(timeout()),this,SLOT(timeUpdate()));
}
void MainWindow::timeUpdate()
{
    QDateTime CurrentTime=QDateTime::currentDateTime();
    QString Timestr=CurrentTime.toString(" yyyy年MM月dd日 hh:mm:ss "); //设置显示的格式
    QStringList timelist = Timestr.split(" ");
    ui->label_time->setText(timelist.at(2));
    ui->label_day->setText(timelist.at(1));
}

void MainWindow::on_time_btn1_clicked()
{
    if(ui->time_btn1->text()==" "){
        ui->time_btn1->setText("\n");
        ui->label_time1->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_01.png);");
        timeAlarmClock.alarm_clocktime1 = ui->dateTimeEdit_1->dateTime().toTime_t();
    }else{
        ui->time_btn1->setText(" ");
        ui->label_time1->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_02.png);");
        timeAlarmClock.alarm_clocktime1 = 0;
    }
}

void MainWindow::on_time_btn2_clicked()
{
    if(ui->time_btn2->text()==" "){
        ui->time_btn2->setText("\n");
        ui->label_time2->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_01.png);");
        timeAlarmClock.alarm_clocktime2 = ui->dateTimeEdit_2->dateTime().toTime_t();
    }else{
        ui->time_btn2->setText(" ");
        ui->label_time2->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_02.png);");
        timeAlarmClock.alarm_clocktime2 = 0;
    }
}

void MainWindow::on_time_btn3_clicked()
{
    if(ui->time_btn3->text()==" "){
        ui->time_btn3->setText("\n");
        ui->label_time3->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_01.png);");
        timeAlarmClock.alarm_clocktime3 = ui->dateTimeEdit_3->dateTime().toTime_t();
    }else{
        ui->time_btn3->setText(" ");
        ui->label_time3->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_02.png);");
        timeAlarmClock.alarm_clocktime3 = 0;
    }
}

void MainWindow::on_time_btn4_clicked()
{
    if(ui->time_btn4->text()==" "){
        ui->time_btn4->setText("\n");
        ui->label_time4->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_01.png);");
        timeAlarmClock.alarm_clocktime4 = ui->dateTimeEdit_4->dateTime().toTime_t();
    }else{
        ui->time_btn4->setText(" ");
        ui->label_time4->setStyleSheet("background-image: url(:/images出行助手/闹钟开关_02.png);");
        timeAlarmClock.alarm_clocktime4 = 0;
    }
}
void MainWindow::mylineedit_alarmclock_init()
{
    lineEdit_alarm_clock1 =new My_lineEdit(ui->tab_alarmclock);
    lineEdit_alarm_clock2 =new My_lineEdit(ui->tab_alarmclock);
    lineEdit_alarm_clock3 =new My_lineEdit(ui->tab_alarmclock);
    lineEdit_alarm_clock4 =new My_lineEdit(ui->tab_alarmclock);
    lineEdit_alarm_clock1->setObjectName("lineEdit_alarm_clock1");
    lineEdit_alarm_clock1->setGeometry(QRect(160, 130, 191, 41));
    lineEdit_alarm_clock1->setText("闹钟1(上班)");
    lineEdit_alarm_clock2->setObjectName("lineEdit_alarm_clock2");
    lineEdit_alarm_clock2->setGeometry(QRect(500, 130, 191, 41));
    lineEdit_alarm_clock2->setText("闹钟2(下班)");
    lineEdit_alarm_clock3->setObjectName("lineEdit_alarm_clock3");
    lineEdit_alarm_clock3->setGeometry(QRect(160, 310, 191, 41));
    lineEdit_alarm_clock3->setText("闹钟3");
    lineEdit_alarm_clock4->setObjectName("lineEdit_alarm_clock4");
    lineEdit_alarm_clock4->setGeometry(QRect(500, 310, 191, 41));
    lineEdit_alarm_clock4->setText("闹钟4");

    syszuxpinyin_alarm_clock1 =new SyszuxPinyin();
    syszuxpinyin_alarm_clock2 =new SyszuxPinyin();
    syszuxpinyin_alarm_clock3 =new SyszuxPinyin();
    syszuxpinyin_alarm_clock4 =new SyszuxPinyin();
    connect(lineEdit_alarm_clock1,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_alarm_clock1(QString)));
    connect(lineEdit_alarm_clock2,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_alarm_clock2(QString)));
    connect(lineEdit_alarm_clock3,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_alarm_clock3(QString)));
    connect(lineEdit_alarm_clock4,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_alarm_clock4(QString)));
    connect(syszuxpinyin_alarm_clock1,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_alarm_clock1(QString)));
    connect(syszuxpinyin_alarm_clock2,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_alarm_clock2(QString)));
    connect(syszuxpinyin_alarm_clock3,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_alarm_clock3(QString)));
    connect(syszuxpinyin_alarm_clock4,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_alarm_clock4(QString)));

}
void MainWindow::keyboardshow_alarm_clock1(QString data)
{
    syszuxpinyin_alarm_clock1->lineEdit_window->setText(data);
    syszuxpinyin_alarm_clock1->resize(800,310);
    syszuxpinyin_alarm_clock1->move(20,100);
    syszuxpinyin_alarm_clock1->show();
}
void MainWindow::keyboardshow_alarm_clock2(QString data)
{
    syszuxpinyin_alarm_clock2->lineEdit_window->setText(data);
    syszuxpinyin_alarm_clock2->resize(800,310);
    syszuxpinyin_alarm_clock2->move(20,100);
    syszuxpinyin_alarm_clock2->show();
}
void MainWindow::keyboardshow_alarm_clock3(QString data)
{
    syszuxpinyin_alarm_clock3->lineEdit_window->setText(data);
    syszuxpinyin_alarm_clock3->resize(800,310);
    syszuxpinyin_alarm_clock3->move(20,100);
    syszuxpinyin_alarm_clock3->show();
}
void MainWindow::keyboardshow_alarm_clock4(QString data)
{
    syszuxpinyin_alarm_clock4->lineEdit_window->setText(data);
    syszuxpinyin_alarm_clock4->resize(800,310);
    syszuxpinyin_alarm_clock4->move(20,100);
    syszuxpinyin_alarm_clock4->show();
}
void MainWindow::confirmString_alarm_clock1(QString gemfield)
{
     lineEdit_alarm_clock1->setText(gemfield);
}
void MainWindow::confirmString_alarm_clock2(QString gemfield)
{
     lineEdit_alarm_clock2->setText(gemfield);
}
void MainWindow::confirmString_alarm_clock3(QString gemfield)
{
     lineEdit_alarm_clock3->setText(gemfield);
}
void MainWindow::confirmString_alarm_clock4(QString gemfield)
{
     lineEdit_alarm_clock4->setText(gemfield);
}
