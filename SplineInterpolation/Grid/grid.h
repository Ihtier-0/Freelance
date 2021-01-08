#ifndef GRID_H
#define GRID_H

#include "ObjectToDraw/objecttodraw.h"

class Grid : public ObjectToDraw
{
public:
    Grid(const qreal& a_left, const qreal& a_right,
         const qreal& a_top, const qreal& a_bottom, const qreal& a_step);

    virtual void draw(const QMatrix4x4 &viewMatrix);
private:
    qreal m_left;
    qreal m_right;
    qreal m_top;
    qreal m_bottom;
    qreal m_step;
};

#endif // GRID_H
