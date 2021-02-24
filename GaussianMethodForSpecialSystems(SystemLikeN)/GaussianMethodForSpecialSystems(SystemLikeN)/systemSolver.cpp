#include "systemSolver.h"
#include "utils.h"

systemSolver::systemSolver(const std::vector<double>& a, //решает систему
    const std::vector<double>& b,
    const std::vector<double>& c,
    const std::vector<double>& f,
    const std::vector<double>& p,
    const std::vector<double>& q,
    const int& k) : m_k(k), m_a(a), m_b(b), m_c(c), m_f(f), m_q(q), m_p(p) {}

bool systemSolver::solveSystem(std::vector<double>& answer)
{
    std::vector<std::vector<double>> matrix;

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
    std::reverse(answer.begin() , answer.end());

    return true;
}

bool systemSolver::FirstStep()
{
    int size = m_a.size();

    double R;

    for(int i = 0; i < size - 1; ++i)
    {
        R = m_b[i];

        if (R == 0)
        {
            return false;
        }

        m_b[i] = 1;
        R = 1 / R;

        m_a[i] *= R;
        m_c[i] *= R;
        m_q[i] *= R;
        m_p[i] *= R;
        m_f[i] *= R;

        R = m_c[i + 1];
        m_c[i + 1] = 0;
        m_b[i + 1] -= R * m_a[i];
        m_q[i + 1] -= R * m_q[i];
        m_f[i + 1] -= R * m_f[i];
        m_p[i + 1] -= R * m_p[i];

        m_a[size - m_k - 2] = m_q[size - m_k - 2];
        m_b[size - m_k - 1] = m_q[size - m_k - 1];
        m_q[size - m_k] = m_c[size - m_k];
        m_b[size - m_k] = m_p[size - m_k];
        m_a[size - m_k - 1] = m_p[size - m_k - 1];
        m_p[size - m_k + 1] = m_c[size - m_k + 1];

        /*
        m_q[size - m_k - 2] = m_a[size - m_k - 2];
        m_q[size - m_k - 1] = m_b[size - m_k - 1];
        m_q[size - m_k] = m_c[size - m_k];
        m_p[size - m_k] = m_b[size - m_k];
        m_p[size - m_k - 1] = m_a[size - m_k - 1];
        m_p[size - m_k + 1] = m_c[size - m_k + 1];
        */
    }

    R = m_b[size - 1];

    if (R == 0)
    {
        return false;
    }
    m_b[size - 1] = 1;
    R = 1 / R;

    m_a[size - 1] *= R;
    m_c[size - 1] *= R;
    m_q[size - 1] *= R;
    m_p[size - 1] *= R;
    m_f[size - 1] *= R;

    return true;
}

bool systemSolver::SecondStep()
{
    int size = m_a.size();

    double R;

    for (int i = size - 2; i >= 0; --i)
    {
        R = m_a[i];
        m_a[i] = 0;
        m_p[i] -= R * m_p[i + 1];
        m_q[i] -= R * m_q[i + 1];
        m_f[i] -= R * m_f[i + 1];

        m_q[size - m_k - 2] = m_a[size - m_k - 2];
        m_b[size - m_k - 1] = m_q[size - m_k - 1];
        m_c[size - m_k] = m_q[size - m_k];
        m_b[size - m_k] = m_p[size - m_k];
        m_p[size - m_k - 1] = m_a[size - m_k - 1];
        m_c[size - m_k + 1] = m_p[size - m_k + 1];

        if (m_b[i] != 1)
        {
            R = m_b[i];

            if (R == 0)
            {
                return false;
            }

            m_b[i] = 1;
            R = 1 / R;

            m_a[i] *= R;
            m_c[i] *= R;
            m_q[i] *= R;
            m_p[i] *= R;
            m_f[i] *= R;
        }
    }
    return true;
}

bool systemSolver::ThirdStep()
{
    int size = m_a.size();

    double R;

    for (int i = 0; i < size; ++i)
    {
        if (i == size - m_k)
        {
            continue;
        }

        R = m_p[i];
        m_p[i] = 0;
        m_q[i] -= m_q[size - m_k] * R;
        m_f[i] -= m_f[size - m_k] * R;

        m_a[size - m_k - 2] = m_q[size - m_k - 2];
        m_b[size - m_k - 1] = m_q[size - m_k - 1];
        m_c[size - m_k] = m_q[size - m_k];
        m_b[size - m_k] = m_p[size - m_k];
        m_a[size - m_k - 1] = m_p[size - m_k - 1];
        m_c[size - m_k + 1] = m_p[size - m_k + 1];
    }

    return true;
}

bool systemSolver::FourthStep()
{
    int size = m_a.size();

    double R;

    for (int i = 0; i < size; ++i)
    {
        if (i == size - m_k - 1)
        {
            continue;
        }

        R = m_q[i];
        m_q[i] = 0;
        m_f[i] -= m_f[size - m_k - 1] * R;

        m_a[size - m_k - 2] = m_q[size - m_k - 2];
        m_b[size - m_k - 1] = m_q[size - m_k - 1];
        m_c[size - m_k] = m_q[size - m_k];
        m_b[size - m_k] = m_p[size - m_k];
        m_a[size - m_k - 1] = m_p[size - m_k - 1];
        m_c[size - m_k + 1] = m_p[size - m_k + 1];
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const systemSolver& ss)
{
    std::vector<std::vector<double>> matrix;

    fillMatrix(matrix, ss.m_a, ss.m_b, ss.m_c, ss.m_p, ss.m_q, ss.m_k);

    for (int i = 0; i < matrix.size(); ++i)
    {
        out << matrix[i] << '\t' << ss.m_f[i] << '\n';
    }

    return out;
}
