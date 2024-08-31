// Author: Filip Dymczyk
// Description : RLS implementation.

#pragma once
#include <array>
#include "algebra/algebra.h"

template<std::size_t n>
class RecursiveLinearRegression
{
public:
    RecursiveLinearRegression(double const lambda, std::array<double, n> coefficients) : _lambda(lambda) 
    {
        _P = create_diagonal_matrix(n);
    }

    void
    update(std::array<double, n> current_coefficients, std::array<double, n> x, double const y_meas, double const y_calc)
    {
        std::array<double, n> temp_vector = matrix_vector_vector_product(_P, x);
        double const coefficient = vector_vector_scalar_product(x, temp_vector);
        
        std::array<stad::array<double, n>, n> K = scale_vector(matrix_vector_vector_product(_P, x), 1 / (lambda + coefficient));
        
        double const epsilon = y_meas - y_calc;

        _coefficients = add_vectors(current_coefficients, scale_vector(K, epsilon));

        _P = 
    }

    std::array<double, n> const &
    get_coefss() const
    {
        return _coeffs;
    }
private:
    double _lambda {};
    std::array<std::array<double, n>, n> _P {};
    std::array<double, n> _coefficients {};
};