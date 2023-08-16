#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>
#include "mainwindow.h"

class myThread : public QThread
{
    Q_OBJECT
public:
    myThread(MainWindow *w);

private:
    MainWindow* w;
    void run() override{

    }
signals:

};

#endif // THREAD_H
