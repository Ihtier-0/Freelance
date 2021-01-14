#include <QApplication>
#include <QtMath>

#include "mainwindow.h"
#include "Viewport/viewport.h"
#include "Camera/camera.h"
#include "ExplicitGraphOfFunction/explicitgraphoffunction.h"
#include "Grid/grid.h"
#include "CubicSpline/cubicspline.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camera c;
    Viewport v(&c);

    ExplicitGraphOfFunction Graph(
                [](const qreal &x) -> qreal
    {
        return qSqrt(1 + 3 * x * x)/qSqrt(2 + 5 * x * x);
    }, 0.25, -1, 1);

    v.addObject(&Graph);

    Grid G(-1, 1, 1, -1, 0.5);
    v.addObject(&G);

    cubicSpline S([](const qreal &x) -> qreal
    {
        return qSqrt(1 + 3 * x * x)/qSqrt(2 + 5 * x * x);
    }, 0.25, -1, 1);
    v.addObject(&S);

    MainWindow w(&v);
    w.show();
    return a.exec();
}
