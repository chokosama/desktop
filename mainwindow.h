#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QClipboard>
#include <QApplication>
#include <QString>
#include <QList>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QWindowStateChangeEvent>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QLineEdit>

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
};



#endif // MAINWINDOW_H
