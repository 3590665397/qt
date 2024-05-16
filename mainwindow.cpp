#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <QTextStream>
#include <QFile>
#include <linux/input.h>
#define EXIT_FAN (_IO('f', 7))
#define FAN_UP (_IO('f', 5))
#define FAN_DOWN (_IO('f', 6))
#define INIT_FAN (_IO('f', 4))
#define BOARD_TYPE_FSMP1A            1
#define BOARD_TYPE_FSMP1C            2

static int get_board_type(void)
{
    char searchText[]="-fsmp1a";
    size_t len_searchText;
    FILE *file;
    char string[128];
    int len_string;
    int i = 0;

    memset(string, 0x0, sizeof(string));

    file = fopen("/proc/device-tree/compatible", "r");
    if (file == nullptr) {
        qDebug("fails to open /proc/device-tree/compatible\n");
        return -1;
    }

    len_searchText = strlen(searchText);

    while(fgets(string, sizeof(string), file) != nullptr)
    {
        len_string = strlen(string);
        for(i = 0 ; i < len_string ; i++) {
            if(strncmp(searchText, (string + i), len_searchText) == 0) {
                fclose(file);
                return BOARD_TYPE_FSMP1A;
            }
        }
    }
    fclose(file);
    return BOARD_TYPE_FSMP1C;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    system("systemctl restart ntpd.service");

    QIcon icon0A,icon1B,icon2B,icon3B;
    QSize  size;
    QMatrix matrix;
    size.setHeight(180);
    size.setWidth(120);
    matrix.rotate(90);      //旋转90度
    ui->tabWidget->setIconSize(size);

    icon0A.addPixmap(QPixmap(":/images出行助手/选中_01.png").transformed(matrix,Qt::SmoothTransformation));//改变-平滑变换
    ui->tabWidget->setTabIcon(0,icon0A);

    icon1B.addPixmap(QPixmap(":/images出行助手/选中_02.png").transformed(matrix,Qt::SmoothTransformation));
    ui->tabWidget->setTabIcon(1,icon1B);
    icon2B.addPixmap(QPixmap(":/images出行助手/选中_03.png").transformed(matrix,Qt::SmoothTransformation));
    ui->tabWidget->setTabIcon(2,icon2B);
    icon3B.addPixmap(QPixmap(":/images出行助手/选中_04.png").transformed(matrix,Qt::SmoothTransformation));
    ui->tabWidget->setTabIcon(3,icon3B);
    ui->tabWidget->setFocusPolicy(Qt::NoFocus);//实现点击无焦点,去除虚线框



    ui->label_yuyin->setStyleSheet("QLabel{background: transparent;}");
    ui->label_return->setStyleSheet("QLabel{background: transparent;}");
    ui->pushButton_clear->setStyleSheet("QPushButton{background: transparent;}");
    ui->pushButton_clear->setFlat(true);
    ui->pushButton_video->setStyleSheet("QPushButton{background: transparent;}");
    ui->pushButton_video->setFlat(true);

    ui->label_day->setStyleSheet("QLabel{background: transparent;font: 12pt \"Source Code Pro\";color: rgb(255, 255, 255);}");
    ui->label_time->setStyleSheet("QLabel{background: transparent;font: 19pt \"Source Code Pro\";color: rgb(255, 255, 255);}");

    ui->time_btn1->setStyleSheet("QPushButton{background: transparent;}");
    ui->time_btn1->setFlat(true);
    ui->time_btn1->setText(" ");

    ui->time_btn2->setStyleSheet("QPushButton{background: transparent;}");
    ui->time_btn2->setFlat(true);
    ui->time_btn2->setText(" ");

    ui->time_btn3->setStyleSheet("QPushButton{background: transparent;}");
    ui->time_btn3->setFlat(true);
    ui->time_btn3->setText(" ");

    ui->time_btn4->setStyleSheet("QPushButton{background: transparent;}");
    ui->time_btn4->setFlat(true);
    ui->time_btn4->setText(" ");
    ui->dateTimeEdit_1->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());
    life_citybtn_init();
    mapinit();
    loc_time_init();
    mylineedit_alarmclock_init();
    mylineedit_map_init();
    timeAlarmClock.start();
    QProcess *m_process = new QProcess;
    QStringList arguments;
    arguments << "-c" << "0" << "cset" << "numid=2" << "on";
    m_process->start("amixer",arguments);
    m_process->waitForFinished();
    arguments.clear();
    m_process->close();
    arguments << "-c" << "0" << "cset" << "numid=1" << "90%";
    m_process->start("amixer",arguments);
    m_process->waitForFinished();
    arguments.clear();
    m_process->close();
    arguments << "-c" << "0" << "cset" << "numid=3" << "90%";
    m_process->start("amixer",arguments);
    m_process->waitForFinished();
    arguments.clear();
    m_process->close();
    arguments << "-c" << "0" << "cset" << "numid=7" << "off";
    m_process->start("amixer",arguments);
    m_process->waitForFinished();
    arguments.clear();
    m_process->close();
    arguments << "-c" << "0" << "cset" << "numid=16" << "2";
    m_process->start("amixer",arguments);
    m_process->waitForFinished();
    arguments.clear();
    m_process->close();
    arguments << "-c" << "0" << "cset" << "numid=17" << "2";
    m_process->start("amixer",arguments);
    m_process->waitForFinished();
    arguments.clear();
    m_process->close();
    m_myrecord = new myrecord;// 创建一个myrecord对象
    connect(this, SIGNAL(mysignalflag()), m_myrecord, SLOT(myslotflag()));
    closeclock = new TimeAlarmClock;
    connect(ui->closebutton,SIGNAL(clicked()),closeclock,SLOT(closeclock()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_video_pressed()
{
    ui->label->setStyleSheet("background-image: url(:/images出行助手/松开识别.png);");
    static int flag_switch = 0;
        flag_switch = !flag_switch;
        if (flag_switch)
        {
            m_myrecord->start();
        }
}

void MainWindow::on_pushButton_video_released()
{
    ui->label->setStyleSheet("background-image: url(:/images出行助手/开始说话.png);");
    emit mysignalflag();
    Speech my_speech;
    QString text =my_speech.speechIdentify("/root/rec1.wav");
    ui->label_yuyin->setText(text);
    audioCtrl(text);

}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->label_yuyin->clear();
}
void MainWindow::audioCtrl(QString text)
{
    //板子类型
    int type =get_board_type();

    if(text == "开灯。")
    { 
        if(type==BOARD_TYPE_FSMP1C)
        {
            system("echo 1 > /sys/class/leds/user1/brightness");
            system("echo 1 > /sys/class/leds/user2/brightness");
            system("echo 1 > /sys/class/leds/user3/brightness");
        }
        else if(type==BOARD_TYPE_FSMP1A)
        {
            system("echo 1 > /sys/class/leds/led1/brightness");
            system("echo 1 > /sys/class/leds/led2/brightness");
            system("echo 1 > /sys/class/leds/led3/brightness");
        }
        ui->label_return->setText("灯已打开");
    }
    else if(text == "关灯。")
    {
        if(type==BOARD_TYPE_FSMP1C)
        {
            system("echo 0 > /sys/class/leds/user1/brightness");
            system("echo 0 > /sys/class/leds/user2/brightness");
            system("echo 0 > /sys/class/leds/user3/brightness");
        }
        else if(type==BOARD_TYPE_FSMP1A)
        {
            system("echo 0 > /sys/class/leds/led1/brightness");
            system("echo 0 > /sys/class/leds/led2/brightness");
            system("echo 0 > /sys/class/leds/led3/brightness");
        }
        ui->label_return->setText("灯已关闭");
    }
    else if(text == "报警。")
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
        ui->label_return->setText("蜂鸣器已报警");
    }
    else if(text == "关闭。")
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
        ui->label_return->setText("蜂鸣器报警已关闭");
    }
    else if(text == "关风扇。")
    {
        if(type==BOARD_TYPE_FSMP1A)
            system("echo 0 > /sys/class/hwmon/hwmon1/pwm1");
        else if(type==BOARD_TYPE_FSMP1C)
        {
            unsigned char arg;
            Ioctl(EXIT_FAN,&arg);
        }
        ui->label_return->setText("风扇已关闭");
    }
    else if(text == "开风扇。")
    {
        if(type==BOARD_TYPE_FSMP1A)
            system("echo 255 > /sys/class/hwmon/hwmon1/pwm1");
        else if(type==BOARD_TYPE_FSMP1C)
        {
            unsigned char arg;
            Ioctl(EXIT_FAN,&arg);
            Ioctl(INIT_FAN,&arg);
            Ioctl(FAN_UP,&arg);
        }
        ui->label_return->setText("风扇已打开");
    }
    else if(text == "温度。")
    {
       QString tem = temCollect();
       ui->label_return->setText(QString("此时温度为:").append(tem).append("'C"));
    }
    else if(text == "湿度。")
    {
        QString hum = humCollect();
        ui->label_return->setText(QString("此时湿度为:").append(hum).append("%"));
    }

}
void MainWindow::Ioctl(unsigned long cmd, void* arg)
{
    int fd;
    fd = open("/dev/sensor-manage", O_RDWR);
    if(fd < 0) {
        perror("open");
    }
    if(ioctl(fd, cmd, arg))
        perror("ioctl");
}
/*温度湿度*/
QString MainWindow::temCollect()
{
    int temp_raw = 0;
    int temp_offset = 0;
    float temp_scale = 0;
    float tem_float =0;
    QString tem;
    const char *device1 ="iio:device0";//温湿度
    /*read temp data*/
    read_sysfs_int(device1, "in_temp_raw", &temp_raw);
    read_sysfs_int(device1, "in_temp_offset", &temp_offset);
    read_sysfs_float(device1, "in_temp_scale", &temp_scale);
    tem_float =(temp_raw + temp_offset) * temp_scale / 1000;
    tem =QString::number(tem_float,'f', 2);
    return tem;
}
QString MainWindow::humCollect()
{
    int hum_raw = 0;
    int hum_offset = 0;
    float hum_scale = 0;
    float hum_float =0;
    QString hum;
    const char *device1 ="iio:device0";//温湿度
    read_sysfs_int(device1, "in_humidityrelative_raw", &hum_raw);
    read_sysfs_int(device1, "in_humidityrelative_offset", &hum_offset);
    read_sysfs_float(device1, "in_humidityrelative_scale", &hum_scale);
    hum_float = (hum_raw + hum_offset) * hum_scale / 1000;
    hum =QString::number(hum_float,'f', 2);
    return hum;
}

int MainWindow::read_sysfs_float(const char *device, const char *filename, float *val)
{
    int ret = 0;
    FILE *sysfsfp;
    char temp[128];
    memset(temp, '0', 128);
    ret = sprintf(temp, "/sys/bus/iio/devices/%s/%s", device, filename);
    if (ret < 0)
        goto error;
    sysfsfp = fopen(temp, "r");
    if (!sysfsfp)
    {
        ret = -errno;
        goto error;
    }
    errno = 0;
    if (fscanf(sysfsfp, "%f\n", val) != 1)
    {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            perror("read_sysfs_float(): Failed to close dir");
        goto error;
    }
    if (fclose(sysfsfp))
        ret = -errno;
error:
    return ret;
}
int MainWindow::read_sysfs_int(const char *device, const char *filename, int *val)
{
    int ret = 0;
    FILE *sysfsfp;
    char temp[128];
    memset(temp, '0', 128);
    ret = sprintf(temp, "/sys/bus/iio/devices/%s/%s", device, filename);
    if (ret < 0)
        goto error;
    sysfsfp = fopen(temp, "r");
    if (!sysfsfp)
    {
        ret = -errno;
        goto error;
    }
    errno = 0;
    if (fscanf(sysfsfp, "%d\n", val) != 1)
    {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            perror("read_sysfs_float(): Failed to close dir");
        goto error;
    }
    if (fclose(sysfsfp))
        ret = -errno;
error:
    return ret;
}

void MainWindow::on_pushButton_beijing_clicked()
{
    LifeWidget *beijinglifeWidget = new LifeWidget(BEIJING);
    beijinglifeWidget->show();
}

void MainWindow::on_pushButton_shanghai_clicked()
{
    LifeWidget *shanghailifeWidget = new LifeWidget(SHANGHAI);
    shanghailifeWidget->show();
}

void MainWindow::on_pushButton_tianjin_clicked()
{
    LifeWidget *tianjinlifeWidget = new LifeWidget(TIANJIN);
    tianjinlifeWidget->show();
}

void MainWindow::on_pushButton_chongqing_clicked()
{
    LifeWidget *chongqinglifeWidget = new LifeWidget(CHONGQING);
    chongqinglifeWidget->show();
}

void MainWindow::on_pushButton_jinan_clicked()
{
    LifeWidget *jinanlifeWidget = new LifeWidget(JINAN);
    jinanlifeWidget->show();
}

void MainWindow::on_pushButton_nanjing_clicked()
{
    LifeWidget *nanjinglifeWidget = new LifeWidget(NANJING);
    nanjinglifeWidget->show();
}

void MainWindow::on_pushButton_wuhan_clicked()
{
    LifeWidget *wuhanlifeWidget = new LifeWidget(WUHAN);
    wuhanlifeWidget->show();
}

void MainWindow::on_pushButton_hangzhou_clicked()
{
    LifeWidget *hangzhoulifeWidget = new LifeWidget(HANGZHOU);
    hangzhoulifeWidget->show();
}

void MainWindow::on_pushButton_guangzhou_clicked()
{
    LifeWidget *guangzhoulifeWidget = new LifeWidget(GUANGZHOU);
    guangzhoulifeWidget->show();
}

void MainWindow::on_pushButton_zhengzhou_clicked()
{
    LifeWidget *zhengzhoulifeWidget = new LifeWidget(ZHENGZHOU);
    zhengzhoulifeWidget->show();
}

void MainWindow::on_pushButton_shenyang_clicked()
{
    LifeWidget *shenyanglifeWidget = new LifeWidget(SHENYANG);
    shenyanglifeWidget->show();
}

void MainWindow::on_pushButton_taiyuan_clicked()
{
    LifeWidget *taiyuanlifeWidget = new LifeWidget(TAIYUAN);
    taiyuanlifeWidget->show();
}
void MainWindow::life_citybtn_init()
{
   ui->pushButton_beijing->setFlat(true);
   ui->pushButton_beijing->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_shanghai->setFlat(true);
   ui->pushButton_shanghai->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_tianjin->setFlat(true);
   ui->pushButton_tianjin->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_chongqing->setFlat(true);
   ui->pushButton_chongqing->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_jinan->setFlat(true);
   ui->pushButton_jinan->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_nanjing->setFlat(true);
   ui->pushButton_nanjing->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_wuhan->setFlat(true);
   ui->pushButton_wuhan->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_hangzhou->setFlat(true);
   ui->pushButton_hangzhou->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_guangzhou->setFlat(true);
   ui->pushButton_guangzhou->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_zhengzhou->setFlat(true);
   ui->pushButton_zhengzhou->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_shenyang->setFlat(true);
   ui->pushButton_shenyang->setStyleSheet("QPushButton{background: transparent;}");

   ui->pushButton_taiyuan->setFlat(true);
   ui->pushButton_taiyuan->setStyleSheet("QPushButton{background: transparent;}");
}
