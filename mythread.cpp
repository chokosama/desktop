#include "mythread.h"
myThread::myThread(QVector<int> *ele,int MaxSize)
{
    this->elementArray=ele;
    this->MaxSize=MaxSize;
}
void myThread::run()
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
