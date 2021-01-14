#ifndef SWEEPMETHOD_H
#define SWEEPMETHOD_H

#include <QVector>

/**
 * b - диагональ, лежащая над главной (нумеруется: [0;n-2])
 * c - главная диагональ матрицы A (нумеруется: [0;n-1])
 * a - диагональ, лежащая под главной (нумеруется: [1;n-1])
 * f - правая часть (столбец)
 * x - решение, массив x будет содержать ответ
 */
void sweepMethod(QVector<double> a, QVector<double> c, QVector<double> b,
                 QVector<double> f, QVector<double>& x);

#endif // SWEEPMETHOD_H
