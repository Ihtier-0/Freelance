#include "circle.h"

#include <QtMath>
#include <QOpenGLFunctions>

#define DEBUG

Circle::Circle(const qreal &a_radius, const quint64& a_amountSegments) : m_radius(a_radius), m_amountSegments(a_amountSegments) {}

void Circle::draw(const QMatrix4x4 &viewMatrix)
{
     glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());

     glBegin(GL_POLYGON);

     for(quint64 i = 0; i < m_amountSegments; i++)
     {
        qreal angle = 2.0 * M_PI * qreal(i) / qreal(m_amountSegments);

        qreal dx = m_radius * qCos(angle);
        qreal dy = m_radius * qSin(angle);

        QVector4D v(dx, dy, 0, 1);

        v = viewMatrix * v;

        glVertex2f(v.x(), v.y());
    }

    glEnd();
}

