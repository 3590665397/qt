#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
static QString client_id ;
static QString secret_id ;
const QString baiduImageUrl = "https://aip.baidubce.com/rest/2.0/image-classify/%1/%2?access_token=%3";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /**判断是否填充过秘钥**/
    detecKey();
    on_comboBox_activated(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openBt_clicked()
{
    cameraTorF = true;
    connect(&vapi, &V4l2Api::sendImage, this, &MainWindow::recvImage);
    vapi.start();
}

void MainWindow::on_closeBt_clicked()
{
    cameraTorF = false;
    disconnect(&vapi, &V4l2Api::sendImage, this, &MainWindow::recvImage);
    ui->label->clear();
}
void MainWindow::recvImage(QImage image)
{
    Saveimage = image;
    QPixmap mmp = QPixmap::fromImage(image);
    ui->label->setPixmap(mmp);
}

void MainWindow::on_saveBt_clicked()
{
    if(cameraTorF == false)
    {
         QMessageBox::warning(this, "警告", "请先采集图像");
         return ;
    }
    picTorF = true;
    disconnect(&vapi, &V4l2Api::sendImage, this, &MainWindow::recvImage);
    cameraTorF = false;

    Saveimage.save("./pic.jpg","JPG",100);
    ui->label->setPixmap(QPixmap::fromImage(Saveimage));
}

void MainWindow::on_recognitionBt_clicked()
{
    ui->textEdit->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    if(Keypadding ==false)
    {
        QMessageBox::warning(this, "警告", "请先填充秘钥");
        return ;
    }
    if(picTorF == false)
    {
         QMessageBox::warning(this, "警告", "请先拍照保存图片");
         return ;
    }
    QByteArray img = IamgeProcess::imageBaseTo64ToUrlEncode("pic.jpg");    //image=xxxxxxx
    QByteArray imgData = "image=" + img;               //body
    //获取access_token
    QByteArray replyData;                 //保存回复信息

    QMap<QString, QString> header;        //封装头部信息
    QString resultText;
    header.insert(QString("Content-Type"), QString("application/x-www-form-urlencoded"));
    bool result = Http::post_sync(imgUrl, header, imgData, replyData);
    if (result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();
        QJsonValue val = obj.value("result");
        qDebug()<< obj;
        qDebug()<<"val = "<<val;
        if (val.isArray())
        {
            for(int i=0;i<val.toArray().size();i++)
            {
                QJsonValue first = val.toArray().at(i);
                qDebug()<<"first" <<first;
                if (first.isObject())
                {
                    QJsonObject object = first.toObject();
                        QString name = object.value("name").toString();
                        qDebug() << "name = " << name;

                        QJsonValue scoreValue = object.value("score");
                        QJsonValue probabilityValue = object.value("probability");
                        if(scoreValue.isDouble()){
                            double score = scoreValue.toDouble();
                            QString stringscore = QString::number(score,'f',9);
                            qDebug() << "score" << score;
                            resultText.append(QString(QString::number(i+1)).append(". 名称: ").append(name).append("\n置信度: ").append(stringscore).append("\n"));
                        }
                        if(scoreValue.isString()){
                            QString score = scoreValue.toString();
                            resultText.append(QString(QString::number(i+1)).append(". 名称: ").append(name).append("\n置信度: ").append(score).append("\n"));
                        }
                        if(probabilityValue.isDouble()){
                             double probability = probabilityValue.toDouble();
                             QString stringprobability = QString::number(probability,'f',9);
                             qDebug()<<"probability"<<probability;
                             resultText.append(QString(QString::number(i+1)).append(". 名称: ").append(name).append("\n置信度: ").append(stringprobability).append("\n"));
                        }
                    ui->textEdit->setText(resultText);
                }
            }

//            显示最终结果
            ui->label_3->setText("经图像分析最可能为");
            ui->label_4->setText(val.toArray().at(0).toObject().value("name").toString());
        }
        else{
            ui->textEdit->append("识别不到，请重新拍照识别");
        }
    }
    else{
        ui->textEdit->append("识别不到，请重新拍照识别");
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    Q_UNUSED(index)//忽略未使用的变量 index

    QByteArray img = IamgeProcess::imageBaseTo64ToUrlEncode("pic.jpg");    //image=xxxxxxx
    QByteArray imgData = "image=" + img;               //body
    //获取access_token
    QByteArray replyData;                 //保存回复信息
    client_id = "oEXUYtRAw4iip8SBDcRzhYpr";
    secret_id = "49glCtdsCZCjXBKmGXpD9dXhaKPiYcRt";
    QString url = QString(baiduTokenUrl).arg(client_id,secret_id);
    QMap<QString, QString> header;        //封装头部信息
    header.insert(QString("Content-Type"), QString("application/x-www-form-urlencoded"));

    bool result = Http::post_sync(url, header, imgData, replyData);
    if (result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();
        accessToken = obj.value("access_token").toString();
        qDebug()<<"accessToken"<<accessToken;
    }

    switch (ui->comboBox->currentIndex())
    {
    case 0:
        imgUrl = baiduImageUrl.arg("v1","animal",accessToken);
        break;
    case 1:
        imgUrl = baiduImageUrl.arg("v2","logo",accessToken);
        break;
    case 2:
        imgUrl = baiduImageUrl.arg("v1","classify/ingredient",accessToken);
        break;
    case 3:
        imgUrl = baiduImageUrl.arg("v1","plant",accessToken);
        break;
    }
}

void MainWindow::on_pushButton_ewm_clicked()
{
    qDebug()<<"111";
    if(picTorF == false)
    {
         QMessageBox::warning(this, "警告", "请先拍照保存图片");
         return ;
    }
     QZXing zxing;
     QString imagePth ="./pic.jpg";
     QImage image(imagePth);
     QByteArray byte = zxing.decodeImage(image).toUtf8();//该方法返回QString串，标识图片二维码的内容
     QJsonObject obj = QJsonDocument::fromJson(byte).object();
     system("touch client_id.txt");
     system("touch secret_id.txt");
     client_id = obj.value("client_id").toString();
     secret_id = obj.value("secret_id").toString();
     qDebug()<< "client_id:"<<client_id;
     qDebug()<< "secret_id:"<<secret_id;
     qDebug()<<"baiudu api"<<baiduImageUrl;
     qDebug()<<"baidu token api "<<baiduTokenUrl;
     if(client_id =="")
     {
         QMessageBox::warning(this, "警告", "请重新填充秘钥");
         on_openBt_clicked();
         return ;
     }
     else
     {
         QMessageBox::information(this, "提示", "填充秘钥成功");
         ui->pushButton_ewm->setText("填充完成");
         ui->pushButton_ewm->setEnabled(false);
         Keypadding = true;
         picTorF = false;
         on_comboBox_activated(0);
         on_openBt_clicked();
     }
     /**将秘钥保存到本地****/

     QFile client_idFile("./client_id.txt");
     client_idFile.open(QIODevice::ReadWrite);
     client_idFile.write(client_id.toUtf8());
     client_idFile.close();
     QFile secret_idFile("./secret_id.txt");
     secret_idFile.open(QIODevice::ReadWrite);
     secret_idFile.write(secret_id.toUtf8());
     secret_idFile.close();
}
void MainWindow::detecKey()
{
    /**判断是否填充过秘钥**/
    QFile client_idFile("./client_id.txt");
    if(client_idFile.exists()){
        client_idFile.open(QIODevice::ReadWrite);
        QByteArray cli_id = client_idFile.readAll();
        qDebug()<<cli_id;
        client_id = cli_id;
        Keypadding = true;
        client_idFile.close();
    }else{
        Keypadding = false;
    }

    QFile secret_idFile("./secret_id.txt");
    if(secret_idFile.exists()){
        secret_idFile.open(QIODevice::ReadWrite);
        QByteArray sec_id = secret_idFile.readAll();
        qDebug()<<sec_id;
        secret_id = sec_id;
        ui->pushButton_ewm->setEnabled(false);
        ui->pushButton_ewm->setText("填充完成");
        Keypadding = true ;
        secret_idFile.close();
    }else{
        Keypadding = false;
    }
}
