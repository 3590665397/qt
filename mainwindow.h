#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMovie>
#include <QImage>
#include <QListView>
#include <QUdpSocket>
#include <QHostInfo>
#include <QAudioInput>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QAudioFormat>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QPropertyAnimation>
#include "speech.h"
#include "lifewidget.h"
#include <QtWebKit>
#include <QWebFrame>
#include <QtWebKitWidgets/QWebView>
#include "timealarmclock.h"
#include "syszuxpinyin.h"
#include "my_lineedit.h"
#include "myrecord.h"
class myrecord;
#define BEIJING    "101010100"
#define SHANGHAI   "101020100"
#define TIANJIN    "101030100"
#define CHONGQING  "101040100"
#define JINAN      "101120101"
#define NANJING    "101190101"
#define WUHAN      "101200101"
#define HANGZHOU   "101210101"
#define GUANGZHOU  "101280101"
#define ZHENGZHOU  "101210101"
#define SHENYANG   "101070101"
#define TAIYUAN    "101100101"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SyszuxPinyin *syszuxpinyin_alarm_clock1;
    SyszuxPinyin *syszuxpinyin_alarm_clock2;
    SyszuxPinyin *syszuxpinyin_alarm_clock3;
    SyszuxPinyin *syszuxpinyin_alarm_clock4;
    My_lineEdit *lineEdit_alarm_clock1;
    My_lineEdit *lineEdit_alarm_clock2;
    My_lineEdit *lineEdit_alarm_clock3;
    My_lineEdit *lineEdit_alarm_clock4;
    SyszuxPinyin *syszuxpinyin_mapItinerary_start;
    SyszuxPinyin *syszuxpinyin_mapItinerary_end;
    My_lineEdit *lineEdit_mapItinerary_start;
    My_lineEdit *lineEdit_mapItinerary_end;

private slots:
    void on_pushButton_video_pressed();

    void on_pushButton_video_released();

    void on_pushButton_clear_clicked();
//map
    void on_pushButton_4_clicked();
    void populateJavaScriptWindowObject();
    void onBtnCallJSClicked();
//life
    void on_pushButton_beijing_clicked();

    void on_pushButton_shanghai_clicked();

    void on_pushButton_tianjin_clicked();

    void on_pushButton_chongqing_clicked();

    void on_pushButton_jinan_clicked();

    void on_pushButton_nanjing_clicked();

    void on_pushButton_wuhan_clicked();

    void on_pushButton_hangzhou_clicked();

    void on_pushButton_guangzhou_clicked();

    void on_pushButton_zhengzhou_clicked();

    void on_pushButton_shenyang_clicked();

    void on_pushButton_taiyuan_clicked();
    void timeUpdate();
    void on_time_btn1_clicked();

    void on_time_btn2_clicked();

    void on_time_btn3_clicked();

    void on_time_btn4_clicked();

    void keyboardshow_alarm_clock1(QString data);
    void keyboardshow_alarm_clock2(QString data);
    void keyboardshow_alarm_clock3(QString data);
    void keyboardshow_alarm_clock4(QString data);
    void confirmString_alarm_clock1(QString gemfield);   //接收键盘发过来的数据
    void confirmString_alarm_clock2(QString gemfield);   //接收键盘发过来的数据
    void confirmString_alarm_clock3(QString gemfield);   //接收键盘发过来的数据
    void confirmString_alarm_clock4(QString gemfield);   //接收键盘发过来的数据

    void keyboardshow_mapItinerary_start(QString data);
    void keyboardshow_mapItinerary_end(QString data);
    void confirmString_mapItinerary_start(QString gemfield);   //接收键盘发过来的数据
    void confirmString_mapItinerary_end(QString gemfield);   //接收键盘发过来的数据
signals:
    void mysignalflag();
private:
    Ui::MainWindow *ui;
//    void RecorderStart(QString fileName);//开始录音
//    void RecorderEnd();//结束录音并转换格式
    QFile *outFile;//录音时的变量
    QAudioInput *my_audio;//录音时的变量
    QAudioFormat audioFormat;//录音时的变量
    void audioCtrl(QString text);
    void Ioctl(unsigned long cmd, void* arg);
    int read_sysfs_float(const char *device, const char *filename, float *val);
    int read_sysfs_int(const char *device, const char *filename, int *val);
    QString temCollect();
    QString humCollect();
    void life_citybtn_init();
    void mapinit();
    myrecord *m_myrecord;
    void loc_time_init();
    QTimer *currentTime;
    TimeAlarmClock timeAlarmClock;
    TimeAlarmClock *closeclock;
    void mylineedit_alarmclock_init();
    void mylineedit_map_init();
};
#endif // MAINWINDOW_H
