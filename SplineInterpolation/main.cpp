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
    // создаем вьюпорт и камеру
    Camera c;
    Viewport v(&c);

    // создаём график функции
    ExplicitGraphOfFunction Graph(
                [](const qreal &x) -> qreal
    {
        return qSqrt(1 + 3 * x * x)/qSqrt(2 + 5 * x * x);
    }, 0.01, -1, 1);

    // добавляем во вьюпорт
    v.addObject(&Graph);

    // Создаём и добавляем во вьюпорт сетку
    Grid G(-1, 1, 1, -1, 0.5);
    v.addObject(&G);

    // создаём и добавляем во вьюпорт кубический сплайн
    cubicSpline S([](const qreal &x) -> qreal
    {
        return qSqrt(1 + 3 * x * x)/qSqrt(2 + 5 * x * x);
    }, 0.01, -1, 1);
    v.addObject(&S);

    // создаём и открываем главное окно
    MainWindow w(&v);
    w.show();
    return a.exec();
}
