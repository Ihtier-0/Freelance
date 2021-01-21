#ifndef CIRCLE_H
#define CIRCLE_H

#include "ObjectToDraw/objecttodraw.h"

class Circle : public ObjectToDraw
{
public:
    Circle(const qreal& a_radius, const quint64& a_amountSegments = 100);
    void draw(const QMatrix4x4 &viewMatrix);

    void animate() {}

private:
    qreal m_radius;
    quint64 m_amountSegments;
};

#endif // CIRCLE_H
