#include "utils.h"
#include "systemSolver.h"

int main()
{
    // srand(time(0));
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

    unsigned int k;

    int numOfIterations = 10;
    
    for (int size = 10; size < 10000; size *= 10)//���� �����������
    {
        for (int border = 10; border < 10000; border *= 10)//���� ������������ ��������
        {
            double accuracy = 0;
            double error = 0;
            for (int iteration = 0; iteration <= numOfIterations; iteration++)//���������� ��������
            {
                generateMatrixForSystemSolver(a, b, c, f, p, q, k, x, size, border);//���������� ������� ��� A*x=f
                systemSolver S(a, b, c, f, p, q, k);//������ �������
                generateMatrixForSystemSolverWhereXIdentity(a, b, c, fIdentity, p, q, k, xIdentity, size, border);//���������� ������� ��� A*xident=fident
                systemSolver SIdentity(a, b, c, fIdentity, p, q, k);//������ �������

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
    }
}