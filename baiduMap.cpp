#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include "CustomStyle.h"
#include <QWebView>
#include <QLineEdit>
#include <QDateTime>
void MainWindow::mapinit()
{
    QWebSettings *settings = QWebSettings::globalSettings();
    settings->setAttribute(QWebSettings::PluginsEnabled, true);//允许插件
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);//JavaScript
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);//
    settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    settings->setFontFamily(QWebSettings::FixedFont,"幼圆");
    ui->webView->setStyle(new CustomStyle());
    ui->webView->load(QUrl("qrc:/map.html"));
    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(populateJavaScriptWindowObject()));

}
void MainWindow::populateJavaScriptWindowObject()
{
   ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("Mywebkit", this);
}
void MainWindow::onBtnCallJSClicked()
{
    QString strVal = QString("callfromqt(\"%1\",\"%2\");").\
            arg(lineEdit_mapItinerary_start->text()).arg(lineEdit_mapItinerary_end->text());
    ui->webView->page()->mainFrame()->evaluateJavaScript(strVal);
}

void MainWindow::on_pushButton_4_clicked()
{
    onBtnCallJSClicked();
}
void MainWindow::mylineedit_map_init()
{

    ui->label_start->setStyleSheet("QLabel{background:rgba(0,0,0,0);color: rgb(238, 238, 236);}");
    ui->label_end->setStyleSheet("QLabel{background:rgba(0,0,0,0);color: rgb(238, 238, 236);}");

    lineEdit_mapItinerary_start =new My_lineEdit(ui->tab_map);
    lineEdit_mapItinerary_end =new My_lineEdit(ui->tab_map);
    lineEdit_mapItinerary_start->setObjectName("lineEdit_mapItinerary_start");
    lineEdit_mapItinerary_start->setGeometry(QRect(620, 140, 161, 41));
    lineEdit_mapItinerary_start->setText("天安门");
    lineEdit_mapItinerary_start->setStyleSheet("My_lineEdit{background:rgba(129,141,82,255);color: rgb(255, 255, 255);}");
    lineEdit_mapItinerary_end->setStyleSheet("My_lineEdit{background:rgba(129,141,82,255);color: rgb(255, 255, 255);}");
    lineEdit_mapItinerary_end->setObjectName("lineEdit_mapItinerary_end");
    lineEdit_mapItinerary_end->setGeometry(QRect(620, 340, 161, 41));
    lineEdit_mapItinerary_end->setText("百度大厦");
    syszuxpinyin_mapItinerary_start =new SyszuxPinyin();
    syszuxpinyin_mapItinerary_end =new SyszuxPinyin();

    connect(lineEdit_mapItinerary_start,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_mapItinerary_start(QString)));
    connect(lineEdit_mapItinerary_end,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_mapItinerary_end(QString)));
    connect(syszuxpinyin_mapItinerary_start,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_mapItinerary_start(QString)));
    connect(syszuxpinyin_mapItinerary_end,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_mapItinerary_end(QString)));
}
void MainWindow::keyboardshow_mapItinerary_start(QString data)
{
    syszuxpinyin_mapItinerary_start->lineEdit_window->setText(data);
    syszuxpinyin_mapItinerary_start->resize(800,310);
    syszuxpinyin_mapItinerary_start->move(20,100);
    syszuxpinyin_mapItinerary_start->show();
}
void MainWindow::keyboardshow_mapItinerary_end(QString data)
{
    syszuxpinyin_mapItinerary_end->lineEdit_window->setText(data);
    syszuxpinyin_mapItinerary_end->resize(800,310);
    syszuxpinyin_mapItinerary_end->move(20,100);
    syszuxpinyin_mapItinerary_end->show();
}
void MainWindow::confirmString_mapItinerary_start(QString gemfield)
{
    lineEdit_mapItinerary_start->setText(gemfield);
}
void MainWindow::confirmString_mapItinerary_end(QString gemfield)
{
    lineEdit_mapItinerary_end->setText(gemfield);
}
