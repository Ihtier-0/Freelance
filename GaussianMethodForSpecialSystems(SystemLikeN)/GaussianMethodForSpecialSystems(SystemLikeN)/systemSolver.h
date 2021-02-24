#pragma once

#include <vector>
#include <iostream>

class systemSolver
{
public:
    systemSolver(const std::vector<double>& a, //решает систему
        const std::vector<double>& b,
        const std::vector<double>& c,
        const std::vector<double>& f,
        const std::vector<double>& p,
        const std::vector<double>& q,
        const int& k);

    bool solveSystem(std::vector<double>& answer);
private:
    bool FirstStep();
    bool SecondStep();
    bool ThirdStep();
    bool FourthStep();

private:
    std::vector<double> m_a;
    std::vector<double> m_b;
    std::vector<double> m_c;
    std::vector<double> m_f;
    std::vector<double> m_p; // k-1 столбец
    std::vector<double> m_q; // k-й столбец

    int m_k;

    friend std::ostream& operator<<(std::ostream& out, const systemSolver& ss);
};