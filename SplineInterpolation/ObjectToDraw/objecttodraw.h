#ifndef OBJECTTODRAW_H
#define OBJECTTODRAW_H

#include <QColor>
#include <QVector3D>
#include <QMatrix4x4>

// объект для рисования
class ObjectToDraw
{
public:
    ObjectToDraw();
    virtual void draw(const QMatrix4x4 &viewMatrix) = 0;

    virtual void setColor(const QColor &color);
    virtual QColor getColor();
protected:
    QColor m_color;
    QMatrix4x4 m_modelMatrix;
};

#endif // OBJECTTODRAW_H
