#include "mainwindow.h"
#include <QMenu>
#include <QSystemTrayIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSystemTrayIcon* trayIcon=new QSystemTrayIcon(QIcon("://contents/icon.jpg"));
    QMenu* trayMenu=new QMenu();
    QAction* restoreAction=trayMenu->addAction("恢复");
    QAction* quitAction=trayMenu->addAction("退出");
    trayIcon->setContextMenu(trayMenu);
    QObject::connect(restoreAction,&QAction::triggered,[&w](){
            w.show();
    });
    QObject::connect(quitAction,&QAction::triggered,[&a](){
        a.exit();
    });
    QObject::connect(trayIcon,&QSystemTrayIcon::activated,[&w,&trayIcon](){
        w.activateWindow();
        w.show();
        trayIcon->hide();
    });

    w.getIcon(trayIcon);
    w.show();
    return a.exec();
}
