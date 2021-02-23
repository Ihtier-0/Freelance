#include "systemSolver.h"
#include "utils.h"

systemSolver::systemSolver(const std::vector<double>& a, //решает систему
    const std::vector<double>& b,
    const std::vector<double>& c,
    const std::vector<double>& f,
    const std::vector<double>& p,
    const int& whenP,
    const std::vector<double>& q,
    const int& whenQ) : m_WhenP(whenP), m_WhenQ(whenQ), m_a(a), m_b(b), m_c(c), m_f(f), m_q(q), m_p(p) {}

bool systemSolver::solveSystem(std::vector<double>& answer)
{
    if (!FirstStep())
    {
        return false;
    }

    if (!SecondStep())
    {
        return false;
    }
    if (!ThirdStep())
    {
        return false;
    }
    if (!FourthStep())
    {
        return false;
    }

    answer = m_f;

    std::reverse(answer.begin(), answer.end());

    return true;
}

bool systemSolver::FirstStep()
{
    double R;
    int size = m_a.size();

    for (int i = 0; i < size; ++i)
    {
        R = 1 / m_b[i];
        m_b[i] = 1;
        m_q[i] *= R;
        m_p[i] *= R;
        m_f[i] *= R;

        if (i < size - 2)
        {
            m_a[i] *= R;
        }

        R = m_c[i + 1];
        m_c[i + 1] = 0;

        m_p[i + 1] -= m_p[i] * R;
        m_q[i + 1] -= m_q[i] * R;
        m_f[i + 1] -= m_f[i] * R;
        m_b[i + 1] -= m_a[i] * R;

        if (i == size - m_WhenP - 3)
        {
            m_a[size - m_WhenP - 2] = m_q[size - m_WhenP - 2];
        }
        if (i == size - m_WhenP - 2)
        {
            m_a[size - m_WhenP - 2] = m_q[size - m_WhenP - 2];
        }
        if (i == size - m_WhenP - 1)
        {

        }
        if (i == size - m_WhenP)
        {

        }
    }

    return true;
}

bool systemSolver::SecondStep()
{
    

    return true;
}

bool systemSolver::ThirdStep()
{
   

    return true;
}

bool systemSolver::FourthStep()
{
    

    return true;
}