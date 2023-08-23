#include "mythread.h"
myThread::myThread(QVector<int> *ele,int MaxSize)
{
    this->type=0;
    this->elementArray=ele;
    this->MaxSize=MaxSize;
}

myThread::myThread(int num,int cases,QList<QString> &contents,QList<QList<QUrl>>& urllist)
{
    this->type=1;
    this->num=num;
    this->contents=contents;
    this->urllist=urllist;
    this->cases=cases;
}


void myThread::run()
{
    if(this->type)
    {
        QFile *file;
        switch(this->cases)
        {
        case 0:
            break;
        case 1:
            file=new QFile("./contents/string"+QString::number(this->num)+".txt");
            if(file->open(QIODevice::ReadOnly))
            {
                (this->contents)[this->num]=QString::fromUtf8(file->readAll());
            }
            else
            {
                file->open(QIODevice::WriteOnly);
            }
            file->close();
            delete file;
            break;
        case 2:
            file=new QFile("./contents/string"+QString::number(this->num)+".txt");
            if(file->open(QIODevice::ReadOnly))
            {
                (this->contents)[this->num]=QString::fromUtf8(file->readAll());
                foreach (QString s,QString::fromUtf8(file->readAll()).split('\n'))
                {
                    QUrl u(s);
                    (this->urllist)[this->num].push_back(u);
                }
            }
            file->close();
            delete file;
            break;
        }
    }
    else
    {
        //读取element.ini文件
        QFile file("./contents/element.ini");
        QByteArray Btemp;
        //通过element.ini文件中的内容来初始化elementArray
        if(file.open(QIODevice::ReadOnly)&&QString::fromUtf8(Btemp=file.readLine())!="")
        {
            for(int i=0;i<MaxSize;i++)
            {
                this->elementArray->push_back(static_cast<int>(Btemp[i]-'0'));
            }
        }
        else
        {
            file.open(QIODevice::WriteOnly);
            for(int i=0;i<MaxSize;i++)
            {
                this->elementArray->push_back(0);
            }
        }
    }
}
