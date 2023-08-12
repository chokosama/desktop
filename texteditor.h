#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QObject>
#include <QTextEdit>
#include <QKeyEvent>
class texteditor : public QTextEdit
{
    Q_OBJECT
public:
    texteditor(QWidget *parent = nullptr):QTextEdit(parent){}
    void keyPressEvent(QKeyEvent *e)
    {

    }
signals:

};

#endif // TEXTEDITOR_H
