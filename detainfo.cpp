#include "detainfo.h"
#include "ui_detainfo.h"
#include <QDebug>
DetaInfo::DetaInfo(int type,QString info,QString city,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetaInfo)
{
    ui->setupUi(this);
    ui->pushButton_close->setStyleSheet("QPushButton{background: transparent;}");
    switch (type) {
        //化妆
    case 0:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/化妆.png);");
        break;
        //旅游
    case 3:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/旅游.png);");
        break;
        //过敏
    case 5:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/过敏.png);");
        break;
        //晾晒
    case 6:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/晾晒.png);");
        break;
        //交通
    case 7:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/交通.png);");
        break;
        //舒适度
    case 8:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/舒适度.png);");
        break;
        //空气质量
    case 9:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/空气.png);");
        break;
        //穿衣
    case 10:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/穿衣.png);");
        break;
        //防晒
    case 11:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/防晒.png);");
        break;
        //感冒
    case 12:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/感冒.png);");
        break;
        //洗车
    case 13:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/洗车.png);");
        break;
        //运动
    case 15:
        ui->label_background->setStyleSheet("background-image: url(:/images出行助手/运动.png);");
        break;
    }
    ui->label_city->setText(city);
    setInfo(info,type);
    ui->label_category->setAlignment(Qt::AlignCenter);
}

DetaInfo::~DetaInfo()
{
    delete ui;
}
void DetaInfo::setInfo(QString info,int type)
{
    qDebug()<<"setINfo";
    QJsonParseError err;
    QJsonDocument json_recv = QJsonDocument::fromJson(info.toUtf8(), &err);//解析json对象
    if (!json_recv.isNull())
    {
        QJsonObject object = json_recv.object();
        if (object.contains("daily"))
        {
            QJsonValue value = object.value("daily");  // 获取指定 key 对应的 value
            if (value.isArray())
            {
                QJsonObject today_life = value.toArray().at(type).toObject();
                QString category = today_life.value("category").toString();
                QString text = today_life.value("text").toString();
                ui->label_category->setText(category);
                ui->label_text->setText(text);
            }
        }
    }
}
void DetaInfo::on_pushButton_close_clicked()
{
    close();
}
