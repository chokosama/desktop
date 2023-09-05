#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QFile>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QUrl>
class myThread : public QThread
{
    Q_OBJECT
public:
    myThread(QVector<int>* ele,int MaxSize);
    myThread(int num,int cases,QList<QString> *contents,QList<QList<QUrl>> *urllist);
    void run() override;

private:
    QVector<int> *elementArray;
    QList<QString> *contents;
    QList<QList<QUrl>> *urllist;
    int MaxSize;
    int cases;
    int num;
    int type;
};

#endif // MYTHREAD_H
