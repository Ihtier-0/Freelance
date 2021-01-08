#include <QColor>
#include <QOpenGLFunctions>

#include "explicitgraphoffunction.h"

ExplicitGraphOfFunction::ExplicitGraphOfFunction(const ExplicitGraphOfFunction::Function &a_y_x,
                                                 const qreal &a_step, const qreal &a_begin, const qreal &a_end)
    : m_y_x(a_y_x), m_step(a_step), m_begin(a_begin), m_end(a_end)
{
    m_color = QColorConstants::DarkMagenta;
}

void ExplicitGraphOfFunction::draw(const QMatrix4x4 &viewMatrix)
{
    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());

    QVector4D begin, end;
    QMatrix4x4 drawMatrix = viewMatrix * m_modelMatrix;

    qreal x = m_begin;

    glLineWidth(3);

    glBegin(GL_LINES);
    for(; x < m_end - m_step ; x += m_step)
    {
        begin = drawMatrix * QVector4D(x, m_y_x(x), 0, 1);
        end = drawMatrix *
                QVector4D(x + m_step, m_y_x(x + m_step), 0, 1);

        glVertex3f(begin.x(), begin.y(), 0);
        glVertex3f(end.x(), end.y(), 0);
    }

    begin = drawMatrix * QVector4D(x, m_y_x(x), 0, 1);
    end = drawMatrix *
            QVector4D(m_end, m_y_x(m_end), 0, 1);

    glVertex3f(begin.x(), begin.y(), 0);
    glVertex3f(end.x(), end.y(), 0);

    glEnd();
}
