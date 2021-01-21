#include "mainwindow.h"
#include "Viewport/viewport.h"
#include "Planet/planet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camera c;
    Viewport v(&c);
    //(расстояние от солнца, время вращения, радиус)
    Planet Jupiter(778, 100 * 11.86, 11.2/2.),
            Saturn(1429, 100 * 29.46, 9.41/2.),
            Uran(2870, 100 * 84.01, 3.98/2.),
            Neptune(4504, 100 * 164.79, 3.81/2.),
            Earth(149, 100 * 1., 1./2.),
            Benera(108.199995, 100 * 0.615, 0.949/2.),
            Mars(227, 100 * 1.88, 0.53),
            Mercurius(57.910006, 100 * 0.241, 0.382/2.);

    Circle Sun(109./2.);
    Sun.setColor(QColorConstants::Yellow);
    Jupiter.setColor(QColor(255, 191, 107));
    Saturn.setColor(QColor(255, 183, 0));
    Uran.setColor(QColor(0, 247, 255));
    Neptune.setColor(QColor(0, 72, 255));
    Earth.setColor(QColorConstants::Green);
    Benera.setColor(QColor(138, 88, 58));
    Mars.setColor(QColor(255, 97, 97));
    Mercurius.setColor(QColor(255, 233, 64));

    // закоментировать если радиус не нужен
    Jupiter.drawOrbit(true);
    Saturn.drawOrbit(true);
    Uran.drawOrbit(true);
    Neptune.drawOrbit(true);
    Earth.drawOrbit(true);
    Benera.drawOrbit(true);
    Mars.drawOrbit(true);
    Mercurius.drawOrbit(true);

    v.addObject(&Jupiter);
    v.addObject(&Saturn);
    v.addObject(&Uran);
    v.addObject(&Neptune);
    v.addObject(&Earth);
    v.addObject(&Benera);
    v.addObject(&Mars);
    v.addObject(&Mercurius);
    v.addObject(&Sun);

    MainWindow w(&v);
    w.show();
    return a.exec();
}
