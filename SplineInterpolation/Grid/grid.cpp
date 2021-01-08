#include "grid.h"

#include <QColor>
#include <QOpenGLFunctions>

Grid::Grid(const qreal &a_left, const qreal &a_right, const qreal &a_top, const qreal &a_bottom, const qreal &a_step)
    : m_left(a_left), m_right(a_right), m_top(a_top), m_bottom(a_bottom), m_step(a_step) {}

void Grid::draw(const QMatrix4x4 &viewMatrix)
{
    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());

    QVector4D begin, end;
    QMatrix4x4 drawMatrix = viewMatrix * m_modelMatrix;

    qreal x = m_left;

    glLineWidth(1);

    glBegin(GL_LINES);

    for(; x <= m_right; x += m_step)
    {
        begin = drawMatrix * QVector4D(x, m_top, 0, 1);
        end = drawMatrix *
                QVector4D(x, m_bottom, 0, 1);

        glVertex3f(begin.x(), begin.y(), 0);
        glVertex3f(end.x(), end.y(), 0);
    }

    x = m_bottom;

    for(; x <= m_top; x += m_step)
    {
        begin = drawMatrix * QVector4D(m_left, x, 0, 1);
        end = drawMatrix *
                QVector4D(m_right, x, 0, 1);

        glVertex3f(begin.x(), begin.y(), 0);
        glVertex3f(end.x(), end.y(), 0);
    }

    glEnd();
}
