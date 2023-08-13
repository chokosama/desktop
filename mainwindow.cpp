#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化剪切板的实列
    this->clipboard=QGuiApplication::clipboard();
    this->index=0;
    ui->textEditor->setReadOnly(true);
    this->setWindowIcon(QIcon("://contents/icon.jpg"));
    //读取element.ini文件
    this->file=new QFile("./contents/element.ini");
    QByteArray Btemp;
    //通过element.ini文件中的内容来初始化elementArray
    if(this->file->open(QIODevice::ReadOnly)&&QString::fromUtf8(Btemp=file->readLine())!="")
    {
        for(int i=0;i<MaxSize;i++)
        {
            this->elementArray.push_back(static_cast<int>(Btemp[i]-'0'));
        }
    }
    else
    {
        this->file->open(QIODevice::WriteOnly);
        for(int i=0;i<MaxSize;i++)
        {
            this->elementArray.push_back(0);
        }
    }
    delete this->file;
    //初始化urllist和contents
    for(int i=0;i<MaxSize;i++)
    {
        QList<QUrl> vurl;
        this->urllist.push_back(vurl);
        QString s;
        this->contents.push_back(s);
    }
    //读内容文件
    for(int i=0;i<MaxSize;i++)
    {
        switch(elementArray[i])
        {
        case 0:
            break;
        case 1:
            this->file=new QFile("./contents/string"+QString::number(i)+".txt");
            if(file->open(QIODevice::ReadOnly))
            {
                this->contents[i]=QString::fromUtf8(file->readAll());
            }
            else
            {
                file->open(QIODevice::WriteOnly);
            }
            file->close();
            delete file;
            break;
        case 2:
            this->file=new QFile("./contents/string"+QString::number(i)+".txt");
            if(file->open(QIODevice::ReadOnly))
            {
                this->contents[i]=QString::fromUtf8(file->readAll());
                foreach (QString s,QString::fromUtf8(file->readAll()).split('\n'))
                {
                    QUrl u(s);
                    this->urllist[i].push_back(u);
                }
            }
            this->file->close();
            delete this->file;
            break;
        }
    }
    //将文本展示在textbrower中
    this->ui->textEditor->setText(this->contents[index]);
    //监听剪切板变化
    connect(clipboard,&QClipboard::changed,this,[=](){
        const QMimeData* clipData=this->clipboard->mimeData();
        //检测是否已经存在
        if(clipData->hasUrls())
        {
            QList<QUrl> qu=clipData->urls();
            foreach (QList<QUrl> urlL,this->urllist) {
                if(qu==urlL)
                    return;
            }
        }
        if(clipData->hasText())
        {
            QString qs=clipData->text();
            foreach (QString s,this->contents) {
                if(qs==s)
                    return;
            }
        }
        this->contents.pop_back();
        this->elementArray.pop_back();
        //将url写入内存
        if(clipData->hasUrls())
        {
            this->urllist.pop_back();
            this->urllist.push_front(clipData->urls());
            QString temp;
            foreach(const QUrl& url,this->urllist[0])
            {
                if(url.isLocalFile())
                {
                    temp+=url.toString();
                    temp+='\n';
                }
            }
            this->contents.push_front(temp);
            elementArray.push_front(2);
        }
        else
        {
            if(clipData->hasText())
            {
                this->contents.push_front(clipData->text());
                elementArray.push_front(1);
            }
        }
        ui->textEditor->setText(contents[index]);
    });
    //绑定上一个按钮
    connect(ui->preBtn,&QPushButton::clicked,this,[=](){
        if(index!=0)
        {
            index--;
            this->ui->label->setText(QString::number(index+1)+"/"+QString::number(MaxSize));
            this->ui->textEditor->setText(this->contents[index]);
        }
        else
        {
            QMessageBox::warning(this,"警告","已经是第一个了");
        }
    });
    //绑定下一个按钮
    connect(ui->nextBtn,&QPushButton::clicked,this,[=](){
        if(index!=MaxSize-1)
        {
            index++;
            this->ui->label->setText(QString::number(index+1)+"/"+QString::number(MaxSize));
            this->ui->textEditor->setText(this->contents[index]);
        }
        else
        {
            QMessageBox::warning(this,"警告","已经是最后一个了");
        }
    });
    //绑定复制按钮
    connect(ui->copyBtn,&QPushButton::clicked,this,[=](){
        if(ui->textEditor->textCursor().hasSelection())
        {
            this->clipboard->setText(ui->textEditor->textCursor().selectedText());
            return;
        }
        if(this->elementArray[index]==0)
        {
            return;
        }
        else if(this->elementArray[index]==1)
        {
            this->clipboard->setText(this->contents[index]);
        }
        else if(this->elementArray[index]==2)
        {
            QMimeData* mimeDatas=new QMimeData;
            QList<QUrl> qls;
            int missFile=0;
            foreach (QUrl u,this->urllist[index])
            {
                if(u.isLocalFile())
                {
                    qls.push_back(u);
                }
                else
                {
                    missFile++;
                }
            }
            mimeDatas->setUrls(qls);
            if(missFile)
            {
                QMessageBox::warning(this,"警告",QString::number(missFile)+"个文件已不存在或发生转移");
            }
            clipboard->setMimeData(mimeDatas);
        }
    });
//绑定搜素功能
    connect(this->ui->searchBtn,&QPushButton::clicked,this,[=](){
        if(this->ui->lineEdit->text()!="")
        {
            for(int i=0;i<MaxSize;i++)
            {
                if(this->contents[i].contains(this->ui->lineEdit->text()))
                {
                    this->index=i;
                    this->ui->textEditor->setText(this->contents[i]);
                    this->ui->label->setText(QString::number(index+1)+"/"+QString::number(MaxSize));
                    return;
                }
            }
        }
        else
        {
            return;
        }
    });
    //添加回车搜素的功能
    connect(this->ui->lineEdit,&QLineEdit::editingFinished,this->ui->searchBtn,[=](){
        emit this->ui->searchBtn->clicked();
    });
}

MainWindow::~MainWindow()
{
    QFile f("./contents/element.ini");
    f.open(QIODevice::WriteOnly);
    QString s;
    foreach (int x, this->elementArray)
    {
        s+=QString::number(x);
    }
    f.write(s.toUtf8());
    f.close();
    for(int i=0;i<MaxSize;i++)
    {
        if(this->elementArray[i]==1)
        {
            QFile fs("./contents/string"+QString::number(i)+".txt");
            fs.open(QIODevice::WriteOnly);
            fs.write(this->contents[i].toUtf8());
            fs.close();
        }
        else if(this->elementArray[i]==2)
        {
            QString temp;
            foreach (QUrl u, this->urllist[i])
            {
                temp+=u.toString()+='\n';
            }
            QFile fs("./contents/string"+QString::number(i)+".txt");
            fs.open(QIODevice::WriteOnly);
            fs.write(temp.toUtf8());
            fs.close();
        }
    }
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type()==QEvent::WindowStateChange)
    {
        QWindowStateChangeEvent *stateChangeEvent=static_cast<QWindowStateChangeEvent*>(event);
        if(stateChangeEvent->oldState()==Qt::WindowNoState&&windowState()==Qt::WindowMinimized)
        {
            this->hide();
            icon->show();
        }
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::getIcon(QSystemTrayIcon* icon)
{
    this->icon=icon;
}
