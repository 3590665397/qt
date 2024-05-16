#ifndef MYRECORD_H
#define MYRECORD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "mainwindow.h"
#include <QMainWindow>

class myrecord:public QThread
{
    Q_OBJECT
public:
    void run();
    myrecord();

signals:
    void mysignal();
public slots:
    void myslotflag();
};

#endif // MYRECORD_H
