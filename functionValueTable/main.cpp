#include "mainwindow.h"
#include "functionValueTable/functionvaluetable.h"

#include <QApplication>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    functionValueTable table([](const qreal& x, const quint64& num, qreal& result, QString& comment) -> bool
    {
        // second option
        qreal zn1 = qCos(x - num),
                zn2 = num;

        if(zn1 == 0 || zn2 == 0)
        {
            comment = "division by 0";
            return false;
        }

        qreal lnArg = (1 - num) / zn1;

        if(lnArg <= 0)
        {
            comment = "logarithm of negative number or 0";
            return false;
        }

        qreal cos = qCos(x);

        if(cos == 0)
        {
            comment = "cos(x) = 0";
            return false;
        }

        qreal sin = qSin(x);

        result = qMin(qLn(lnArg), sin / (cos * num));
        return true;
    }, -1, 1, 0.5);
    MainWindow w(&table);
    w.show();
    return a.exec();
}
