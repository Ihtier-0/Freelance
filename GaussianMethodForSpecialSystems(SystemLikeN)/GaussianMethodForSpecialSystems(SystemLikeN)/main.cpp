#include "utils.h"
#include "systemSolver.h"

int main()
{
    srand(time(0));
    /*
      a,b,c - ������ �������
      f - ������ ������ �����
      fidentity - ������ ������ �����, ��� x=1
      p � q - ������ � ��������� ������� ������� (������� ��������, ������� ������ ������� �������)
      x - ����� ��������� Ax=f
      xidentity - ����� ��������� Axident=fidentity
      xsolve - ������� ��������� Ax=f
      xidentitysolve - ������� ��������� Axident = fident
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

    for (int size = 10; size < 10000; size *= 10)//���� �����������
    {
        for (int border = 10; border < 10000; border *= 10)//���� ������������ ��������
        {
            double accuracy = 0;
            double error = 0;
            for (int iteration = 1; iteration <= numOfIterations; iteration++)//���������� ��������
            {
                generateMatrixForSystemSolver(a, b, c, f, p, q, x, size, border);//���������� ������� ��� A*x=f
                systemSolver S(a, b, c, f, p, q);//������ �������
                generateMatrixForSystemSolverWhereXIdentity(a, b, c, fIdentity, p, q, xIdentity, size, border);//���������� ������� ��� A*xident=fident
                systemSolver SIdentity(a, b, c, fIdentity, p, q);//������ �������

                if (!S.solveSystem(xSolve) || !SIdentity.solveSystem(xIdentitySolve))//���������� ������ ��� ��� �������, ���� ���� �� ���� �� ������
                {
                    --iteration;//������������ �����
                    break;
                }

                accuracy += estimationOfSolutionAccuracy(xIdentity, xIdentitySolve);//��������� ������� � ����� (���������)
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