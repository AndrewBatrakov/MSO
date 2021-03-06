#ifndef MYSTYLE_H
#define MYSTYLE_H

#include <QtWidgets>

class MyStyle : public QCommonStyle
{
public:
    MyStyle();

    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w) const;
    void drawItemText(QPainter *painter, const QRect &rect, int flags, const QPalette &pal, bool enabled, const QString &text, QPalette::ColorRole textRole) const;
    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const;

signals:

public slots:

};

#endif // MYSTYLE_H
