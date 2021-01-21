#include "objecttodraw.h"

ObjectToDraw::ObjectToDraw()
{
    m_modelMatrix.setToIdentity();
}

void ObjectToDraw::setColor(const QColor &color)
{
    m_color = color;
}

QColor ObjectToDraw::getColor()
{
    return m_color;
}
