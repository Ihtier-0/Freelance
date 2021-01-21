#include "planet.h"

#include <QtMath>
#include <QOpenGLFunctions>
#include <Camera/camera.h>

#define DEBUG

Planet::Planet(const qreal& a_distanceFromSun, const qreal& a_rotationTimeAroundSun,
               const qreal& a_radius, const quint64& a_amountSegments)
    : m_radius(a_radius), m_distanceFromSun(a_distanceFromSun),
      m_amountSegments(a_amountSegments), m_planet(m_radius, m_amountSegments), m_rotationTimeAroundSun(a_rotationTimeAroundSun)
{

}

void Planet::draw(const QMatrix4x4 &viewMatrix)
{
     m_planet.setColor(m_color);
     m_planet.draw(viewMatrix * Camera::rotateMatrix(m_angle)
                   * Camera::transferMatrix(QVector3D(0, m_distanceFromSun, 0)));

     if(m_drawOrbit)
     {
         glBegin(GL_LINE_LOOP);

         for(quint64 i = 0; i < m_amountSegments; i++)
         {
            qreal angle = 2.0 * M_PI * qreal(i) / qreal(m_amountSegments);

            qreal dx = m_distanceFromSun * qCos(angle);
            qreal dy = m_distanceFromSun * qSin(angle);

            QVector4D v(dx, dy, 0, 1);

            v = viewMatrix * v;

            glVertex2f(v.x(), v.y());
        }

        glEnd();
     }
}

void Planet::animate()
{
    m_angle += 2 * M_PI / m_rotationTimeAroundSun;

#ifdef DEBUG
    qDebug() << "Planet::animate" << m_angle;
#endif
}

void Planet::drawOrbit(const bool &a_drawOrbit)
{
    m_drawOrbit = a_drawOrbit;
}
