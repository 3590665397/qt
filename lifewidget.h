#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QScrollBar>
#include "detainfo.h"
namespace Ui {
class LifeWidget;
}

class LifeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LifeWidget(QString city,QWidget *parent = nullptr);
    ~LifeWidget();

private:
    Ui::LifeWidget *ui;
    //请求句柄
    QNetworkAccessManager *manager;
    QString replyall;
    QString show_city;
    void sendQuest(QString cityStr);
    void init_network_life();
    void btn_init();
private slots:
    void replyFinished(QNetworkReply *reply); //天气数据处理槽函数
    void on_pushButton_close_clicked();
    void on_pushButton_comfort_clicked();
    void on_pushButton_Sunscreen_clicked();
    void on_pushButton_dresssing_clicked();
    void on_pushButton_makeUp_clicked();
    void on_pushButton_airquality_clicked();
    void on_pushButton_traffic_clicked();
    void on_pushButton_cold_clicked();
    void on_pushButton_allergy_clicked();
    void on_pushButton_airdrying_clicked();
    void on_pushButton_carwash_clicked();
    void on_pushButton_motion_clicked();
    void on_pushButton_Travel_clicked();
};

#endif // LIFEWIDGET_H
