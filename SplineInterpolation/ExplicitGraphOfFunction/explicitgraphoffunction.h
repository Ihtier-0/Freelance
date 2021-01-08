#ifndef EPLICITGRAPHOFFUNCTION_H
#define EPLICITGRAPHOFFUNCTION_H

#include <QVector4D>

#include "ObjectToDraw/objecttodraw.h"

class ExplicitGraphOfFunction : public ObjectToDraw
{
public:
    using Function = std::function<qreal(const qreal &)>;

    ExplicitGraphOfFunction(const Function &a_y_x, const qreal& a_step, const qreal& a_begin, const qreal& a_end);

    virtual void draw(const QMatrix4x4 &viewMatrix) override;
private:
    Function m_y_x;
    qreal m_step;
    qreal m_begin;
    qreal m_end;
};

#endif // EPLICITGRAPHOFFUNCTION_H
