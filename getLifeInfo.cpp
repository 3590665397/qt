#include "lifewidget.h"
#include "ui_lifewidget.h"

//get方法获取信息
void LifeWidget::sendQuest(QString cityStr)
{
//    https://devapi.qweather.com/v7/indices/1d?type=0&location=101100101&key=dd30ddb96beb4d6c9ad3e67d341fb22a
    QString key = "f6503664f1a941cd8868ac9856ce637a";
    QString quest_url = "https://devapi.qweather.com/v7/indices/1d?type=0&location=%1&key=%2";
    quest_url = quest_url.arg(cityStr).arg(key);
    QNetworkRequest quest;
    quest.setUrl(QUrl(quest_url));
    //设置openssl签名配置,否则在ARM上会报错
        QSslConfiguration conf = quest.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    #if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
        conf.setProtocol(QSsl::TlsV1_0);
    #else
        conf.setProtocol(QSsl::TlsV1);
    #endif
        quest.setSslConfiguration(conf);
    manager->get(quest);    /*发送get网络请求*/
}
//数据处理槽函数
void LifeWidget::replyFinished(QNetworkReply *reply)
{
    replyall = reply->readAll();
    reply->deleteLater(); //销毁请求对象
}
void LifeWidget::init_network_life()
{
    manager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));//关联信号和槽
}


