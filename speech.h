#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include "http.h"
#include <QHostInfo>
//    获取Access Token
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "zUPSiQpTBflGPyivyovz986G";
const QString client_secret = "BX0iCZYAAysKA4g9gXhxoYwn4bWNKgAK";
//    语音识别url
const QString baiduSpeechUrl = "https://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";
class Speech:public QObject
{
    Q_OBJECT
public:
    Speech();
    QString speechIdentify(QString fileName);
private:
    QString getJsonValue(QByteArray ba,QString key);
private slots:

signals:

};

#endif // SPEECH_H
