// Author: Filip Dymczyk
// Description : RLS implementation.

#pragma once
#include <array>
#include "algebra.h"

class Recursive_Linear_Regression
{
    using VectorT = std::array<double, 3u>;
    using MatrixT = std::array<std::array<double, 3u>, 3u>;

public:
    Recursive_Linear_Regression(double lambda = 0.99)
    {
        m_lambda = (lambda > 0.0 && lambda <= 1.0) ? lambda : 1.0;
        create_diagonal_matrix(m_P, 1.0);
    }

    void
    update(VectorT const& x, double epsilon);

    VectorT const&
    get_coefficients() const;

    void
    set_initial_coefficients(VectorT const& coefficients);

    void
    set_lambda(double lambda);

    void
    reset();

private:
    double m_lambda {};
    MatrixT m_P {};
    VectorT m_coefficients {};
};