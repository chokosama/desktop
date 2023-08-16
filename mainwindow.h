#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QClipboard>
#include <QApplication>
#include <QString>
#include <QList>
#include <QVector>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QMessageBox>
#include <QWindowStateChangeEvent>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QPainter>
#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeEvent(QEvent *event);
    void getIcon(QSystemTrayIcon* icon);
    void paintEvent(QPaintEvent *event) override;

private:
    int MaxSize=10;
    Ui::MainWindow *ui;
    QClipboard* clipboard;
    QList<QString> contents;
    int index;
    QList<QList<QUrl>> urllist;
    QVector<int> elementArray;
    QFile* file;
    QSystemTrayIcon* icon;
    myThread* thr;
private:
};



#endif // MAINWINDOW_H
