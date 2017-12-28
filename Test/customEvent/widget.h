#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include "CustomEvent.h"
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    bool event(QEvent *e);

protected:
    QLabel *m_label;
};

#endif // WIDGET_H
