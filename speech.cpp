#include "speech.h"

Speech::Speech()
{

}
QString Speech::speechIdentify(QString fileName)
{
//    获取Access Token
    QString tokenUrl =QString(baiduTokenUrl).arg(client_id).arg(client_secret);
    Http my_http;
   ring, QMap<QStQString>header;
    header.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));
    QByteArray requestData;//请求内容
    QByteArray replyData;//url返回内容

   qDebug()<<tokenUrl;
    bool result = my_http.post_sync(tokenUrl,header,requestData,replyData);
    if(result) {
        QString key = "access_token";
        QString accessToken =getJsonValue(replyData,key);
        qDebug()<<accessToken;
        //    语音识别
        QString speechUrl = QString(baiduSpeechUrl).arg(QHostInfo::localHostName()).arg(accessToken);
        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);
        requestData = file.readAll();
        file.close();


        replyData.clear();
//        再次发起请求
        result = my_http.post_sync(speechUrl,header,requestData,replyData);
         if(result) {
             QString key = "result";
             QString retText =getJsonValue(replyData,key);
             qDebug()<<retText;
             return retText;
         }
         else{
             return nullptr;
         }
    }
    else {
        return  "error";
    }
}
QString Speech::getJsonValue(QByteArray ba,QString key)
{
    QJsonParseError parseError;
    QJsonDocument jsondocument = QJsonDocument::fromJson(ba,&parseError);
    if(parseError.error ==QJsonParseError::NoError)
    {
        if(jsondocument.isObject())
        {
            QJsonObject jsonObject = jsondocument.object();
            if(jsonObject.contains(key)){
                QJsonValue jsonvalue = jsonObject.value(key);
                if(jsonvalue.isString())
                    return jsonvalue.toString();
                else if(jsonvalue.isArray()){
                    QJsonArray arr = jsonvalue.toArray();
                    QJsonValue val =arr.at(0);
                    return val.toString();
                }

            }

        }
    }
    return "";

}
