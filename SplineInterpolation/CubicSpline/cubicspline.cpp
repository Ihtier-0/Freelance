#include "cubicspline.h"
#include "SweepMethod/sweepmethod.h"

#include <QOpenGLFunctions>

#include "ExplicitGraphOfFunction/explicitgraphoffunction.h"

#define DEBUG

cubicSpline::cubicSpline(const Function &a_y_x, const qreal& a_step, const qreal& a_begin, const qreal& a_end)
    : m_y_x(a_y_x), m_begin(a_begin), m_end(a_end),  m_step(a_step)
{
    m_color = QColorConstants::Blue;
}

void cubicSpline::draw(const QMatrix4x4 &viewMatrix)
{
    // генерируем набор точек (х, f(x))
    QVector<QVector2D> points = generatePoints();
    // считаем вторые производные в точках
    QVector<qreal> SecondDerivative = calculateSecondDerivative(points);
    quint64 size = points.size();

#ifdef DEBUG
    qDebug() << "points" << points;
#endif
#ifdef DEBUG
    qDebug() << "SecondDerivative" << SecondDerivative;
#endif

    for(quint64 i = 1; i < size; ++i)
    {
        glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());
        // формула кубического сплайна (формула из методички)
        std::function<qreal(const qreal &)> phi = [&](const qreal& x)
        {
            return points[i - 1].y() * (points[i].x() - x) / m_step
                    + points[i].y() * (x - points[i - 1].x()) / m_step
                    +
                    (
                    SecondDerivative[i - 1] * qPow(points[i].x() - x, 3) / m_step +
                    SecondDerivative[i] * qPow(x - points[i - 1].x(), 3) / m_step
                    )/6.
                    - m_step/6. * (SecondDerivative[i - 1] * (points[i].x() - x)
                    + SecondDerivative[i] * (x - points[i - 1].x()));
        };

#ifdef DEBUG
    qDebug() << "phi(" << points[i - 1].x() << ") " << phi(points[i - 1].x());
        qDebug() << "phi("<< points[i].x() << phi(points[i].x());
#endif

        QVector4D begin, end;
        QMatrix4x4 drawMatrix = viewMatrix * m_modelMatrix;

        qreal x = points[i - 1].x();

        glLineWidth(3);

        glBegin(GL_LINES);
        for(; x < points[i].x() - m_step/10. ; x += m_step/10.)
        {
            begin = drawMatrix * QVector4D(x, phi(x), 0, 1);
            end = drawMatrix *
                    QVector4D(x + m_step/10., phi(x + m_step/10.), 0, 1);

            glVertex3f(begin.x(), begin.y(), 0);
            glVertex3f(end.x(), end.y(), 0);

    #ifdef DEBUG
       qDebug() << this << begin << end;
    #endif
        }

        begin = drawMatrix * QVector4D(x, phi(x), 0, 1);
        end = drawMatrix *
                QVector4D(points[i].x(), phi(points[i].x()), 0, 1);

        glVertex3f(begin.x(), begin.y(), 0);
        glVertex3f(end.x(), end.y(), 0);

        glEnd();
    }
}

QVector<QVector2D> cubicSpline::generatePoints()
{
    quint64 size = qAbs(m_begin - m_end) / m_step;

    QVector<QVector2D> result(size); // (x, f(x))

    quint64 i = 0;

    for(; i < size; ++i)
    {
        result[i].setX(m_begin + m_step * i); // x
        result[i].setY(m_y_x(m_begin + m_step * i)); // f(x) // y
    }

    if(m_end != (m_begin + m_step * (i - 1)))
    {
        result.push_back(QVector2D(m_end, m_y_x(m_end)));
    }

    return result;
}

QVector<qreal> cubicSpline::calculateSecondDerivative(const QVector<QVector2D> &points)
{
    quint64 size = points.size();

    QVector<qreal> v(size);

    // генерация вектора правой части
    for(quint64 i = 1; i < size - 1; ++i)
    {
        v[i] = 6. * (points[i + 1].y() - 2. * points[i].y()
                + points[i - 1].y()) / m_step;
    }

    // жёстко закреплённые концы
    v[0] = 6. * (points[1].y() - points[0].y()) / m_step - 6. * 1.;
    v[size - 1] = 6. * 1 - 6 * (points[size - 1].y() - points[size - 2].y()) / m_step;

    QVector<qreal> upperCodiagonal(size);// [0;n-2]
    QVector<qreal> lowerCodiagonal(size);// [0;n-1]
    QVector<qreal> mainDiagonal(size); // [1;n-1]
    QVector<qreal> s(size);

    // генерация главной диагонали, верхней и нижней кодиагонали
    for(quint64 i = 0; i < size; ++i)
    {
        upperCodiagonal[i] = m_step;
        lowerCodiagonal[i] = m_step;
        mainDiagonal[i] = 4 * m_step;
    }

    mainDiagonal[0] = 2 * m_step;
    mainDiagonal[size - 1] = 2 * m_step;

    // решение системы уравнений методом прогонки
    sweepMethod(lowerCodiagonal, mainDiagonal, upperCodiagonal, v, s);


    return s;
}

#include "cubicspline.h"
