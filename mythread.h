#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QFile>
#include <QString>
#include <QByteArray>
class myThread : public QThread
{
    Q_OBJECT
public:
    myThread(QVector<int>* ele,int MaxSize);
    void run() override;
private:
    QVector<int> *elementArray;
    int MaxSize;
};

#endif // MYTHREAD_H
