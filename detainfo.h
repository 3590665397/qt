#ifndef DETAINFO_H
#define DETAINFO_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
namespace Ui {
class DetaInfo;
}

class DetaInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DetaInfo(int type,QString info,QString city,QWidget *parent = nullptr);
    ~DetaInfo();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::DetaInfo *ui;
    void setInfo(QString info,int type);
};

#endif // DETAINFO_H
