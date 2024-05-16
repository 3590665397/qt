#include "lifewidget.h"
#include "ui_lifewidget.h"

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
LifeWidget::LifeWidget(QString city,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LifeWidget)
{
    ui->setupUi(this);
    btn_init();
    if(city == BEIJING){
        show_city ="北京";
    }else if(city == SHANGHAI){
        show_city ="上海";
    }else if(city == TIANJIN){
        show_city ="天津";
    }else if(city == CHONGQING){
        show_city ="重庆";
    }else if(city == JINAN){
        show_city ="济南";
    }else if(city == NANJING){
        show_city ="南京";
    }else if(city == WUHAN){
        show_city ="武汉";
    }else if(city == HANGZHOU){
        show_city ="杭州";
    }else if(city == GUANGZHOU){
        show_city ="广州";
    }else if(city == SHENYANG){
        show_city ="沈阳";
    }else if(city == TAIYUAN){
        show_city ="太原";
    }
    ui->label_city->setText(show_city);
    init_network_life();
    sendQuest(city);
}

LifeWidget::~LifeWidget()
{
    delete ui;
}

void LifeWidget::on_pushButton_close_clicked()
{
    close();
}


void LifeWidget::on_pushButton_comfort_clicked()
{
    DetaInfo *detaInfo_comfort=new DetaInfo(8,replyall,show_city);
    detaInfo_comfort->show();
}

void LifeWidget::on_pushButton_Sunscreen_clicked()
{
    DetaInfo *detaInfo_Sunscreen=new DetaInfo(11,replyall,show_city);
    detaInfo_Sunscreen->show();
}
void LifeWidget::on_pushButton_makeUp_clicked()
{
    DetaInfo *detaInfo_makeUp=new DetaInfo(0,replyall,show_city);
    detaInfo_makeUp->show();
}
void LifeWidget::on_pushButton_dresssing_clicked()
{
    DetaInfo *detaInfo_dresssing=new DetaInfo(10,replyall,show_city);
    detaInfo_dresssing->show();
}

void LifeWidget::on_pushButton_airquality_clicked()
{
    DetaInfo *detaInfo_airquality=new DetaInfo(9,replyall,show_city);
    detaInfo_airquality->show();
}

void LifeWidget::on_pushButton_traffic_clicked()
{
    DetaInfo *detaInfo_traffic=new DetaInfo(7,replyall,show_city);
    detaInfo_traffic->show();
}

void LifeWidget::on_pushButton_cold_clicked()
{
    DetaInfo *detaInfo_cold=new DetaInfo(12,replyall,show_city);
    detaInfo_cold->show();
}

void LifeWidget::on_pushButton_allergy_clicked()
{
    DetaInfo *detaInfo_allergy=new DetaInfo(5,replyall,show_city);
    detaInfo_allergy->show();
}

void LifeWidget::on_pushButton_airdrying_clicked()
{
    DetaInfo *detaInfo_airdrying=new DetaInfo(6,replyall,show_city);
    detaInfo_airdrying->show();
}

void LifeWidget::on_pushButton_carwash_clicked()
{
    DetaInfo *detaInfo_carwash=new DetaInfo(13,replyall,show_city);
    detaInfo_carwash->show();
}

void LifeWidget::on_pushButton_motion_clicked()
{
    DetaInfo *detaInfo_motion=new DetaInfo(15,replyall,show_city);
    detaInfo_motion->show();
}

void LifeWidget::on_pushButton_Travel_clicked()
{
    DetaInfo *detaInfo_Travel=new DetaInfo(3,replyall,show_city);
    detaInfo_Travel->show();
}
void LifeWidget::btn_init()
{
    ui->pushButton_comfort->setFlat(true);
    ui->pushButton_comfort->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_Sunscreen->setFlat(true);
    ui->pushButton_Sunscreen->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_cold->setFlat(true);
    ui->pushButton_cold->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_close->setFlat(true);
    ui->pushButton_close->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_Travel->setFlat(true);
    ui->pushButton_Travel->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_makeUp->setFlat(true);
    ui->pushButton_makeUp->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_motion->setFlat(true);
    ui->pushButton_motion->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_allergy->setFlat(true);
    ui->pushButton_allergy->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_carwash->setFlat(true);
    ui->pushButton_carwash->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_traffic->setFlat(true);
    ui->pushButton_traffic->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_airdrying->setFlat(true);
    ui->pushButton_airdrying->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_dresssing->setFlat(true);
    ui->pushButton_dresssing->setStyleSheet("QPushButton{background: transparent;}");

    ui->pushButton_airquality->setFlat(true);
    ui->pushButton_airquality->setStyleSheet("QPushButton{background: transparent;}");


}
