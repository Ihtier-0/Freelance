#ifndef PLANET_H
#define PLANET_H

#include "ObjectToDraw/objecttodraw.h"
#include "Circle/circle.h"
#include "Camera/camera.h"

class Planet : public ObjectToDraw
{
public:
    Planet(const qreal& a_distanceFromSun, const qreal& a_rotationTimeAroundSun,
           const qreal& a_radius, const quint64& a_amountSegments = 100);
    void draw(const QMatrix4x4 &viewMatrix);

    void animate();
    void drawOrbit(const bool& a_drawOrbit);
private:
    qreal m_radius;
    qreal m_distanceFromSun;
    quint64 m_amountSegments;
    Circle m_planet;
    qreal m_angle = 0;
    qreal m_rotationTimeAroundSun;
    bool m_drawOrbit = false;
};

#endif // PLANET_H
