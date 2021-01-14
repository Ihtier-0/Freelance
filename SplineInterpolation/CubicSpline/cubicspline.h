#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include "ObjectToDraw/objecttodraw.h"

#include<QVector>
#include<QVector2D>

class cubicSpline : public ObjectToDraw
{
public:
    using Function = std::function<qreal(const qreal &)>;

    cubicSpline(const Function &a_y_x, const qreal& a_step, const qreal& a_begin, const qreal& a_end);
    void draw(const QMatrix4x4 &viewMatrix) override;
private:
    QVector<QVector2D> generatePoints();

    QVector<qreal> calculateSecondDerivative(const QVector<QVector2D>& point);

    // функция по которой строится сплайн
    Function m_y_x;
    qreal m_begin;
    qreal m_end;
    qreal m_step;
};

#endif // CUBICSPLINE_H
