#include "utils.h"
#include "systemSolver.h"

int main()
{
    srand(time(0));
    /*
      a,b,c - задают матрицу
      f - вектор правой части
      fidentity - вектор правой части, где x=1
      p и q - первый и последний столбец матрицы (векторы столбцов, которые портят матрицы системы)
      x - ответ уравнения Ax=f
      xidentity - ответ уравнения Axident=fidentity
      xsolve - решение уравнения Ax=f
      xidentitysolve - решение уравнения Axident = fident
    */
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> f;
    std::vector<double> fIdentity;
    std::vector<double> p;
    std::vector<double> q;

    std::vector<double> x;
    std::vector<double> xIdentity;
    std::vector<double> xSolve;
    std::vector<double> xIdentitySolve;

    int size = 5;
    int border = 10;

    unsigned int whenP;
    unsigned int whenQ;

    generateMatrixForSystemSolver(a, b, c, f, p, whenP, q, whenQ, x, size, border);

    systemSolver s(a, b, c, f, p, whenP, q, whenQ);

    s.solveSystem(xSolve);

    for (int i = 0; i < size; ++i)
    {
        std::cout << xSolve[i] << ' ';
    }
    std::cout << '\n';

    /*
    int numOfIterations = 2;

    for (int size = 10; size < 10000; size *= 10)//цикл размерности
    {
        for (int border = 10; border < 10000; border *= 10)//цикл максимальных значений
        {
            double accuracy = 0;
            double error = 0;
            for (int iteration = 1; iteration <= numOfIterations; iteration++)//количество итераций
            {
                generateMatrixForSystemSolver(a, b, c, f, p, q, x, size, border);//генерирует матрицу для A*x=f
                systemSolver S(a, b, c, f, p, q);//решает систему
                generateMatrixForSystemSolverWhereXIdentity(a, b, c, fIdentity, p, q, xIdentity, size, border);//генерирует матрицу для A*xident=fident
                systemSolver SIdentity(a, b, c, fIdentity, p, q);//решает систему

                if (!S.solveSystem(xSolve) || !SIdentity.solveSystem(xIdentitySolve))//необходимо решить все две системы, если хотя бы одна не решена
                {
                    --iteration;//возвращаемся назад
                    break;
                }

                accuracy += estimationOfSolutionAccuracy(xIdentity, xIdentitySolve);//прошарить формулу в лабах (методичке)
                error += relativeSolutionError(x, xSolve);
            }
            accuracy /= numOfIterations;
            error /= numOfIterations;

            std::cout << "Size: " << size
                << "\tborder: " << border
                << "\terror: " << error
                << "\taccuracy: " << accuracy << '\n';
        }
    }*/
}