#include "sweepmethod.h"

// метод прогонки (формулы из википедии)
void sweepMethod(QVector<double> a, QVector<double> c, QVector<double> b, QVector<double> f, QVector<double> &x)
{
    qreal m;

    quint64 size = a.size();

    for (quint64 i = 1; i < size; i++)
    {
        m = a[i]/c[i-1];
        c[i] = c[i] - m*b[i-1];
        f[i] = f[i] - m*f[i-1];
    }

    x[size-1] = f[size-1]/c[size-1];

    for (int i = size - 2; i >= 0; i--)
    {
        x[i]=(f[i]-b[i]*x[i+1])/c[i];
    }
}
