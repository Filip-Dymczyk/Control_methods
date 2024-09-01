// Author: Filip Dymczyk
// Description : RLS implementation.

#pragma once
#include <array>
#include "algebra/algebra.h"

template<std::size_t n>
class RecursiveLinearRegression
{
    using VectorT = std::array<double, n>;
    using MatrixT = std::array<std::array<double, n>, n>;
public:
    RecursiveLinearRegression(double const lambda, std::array<double, n> coefficients) : _lambda(lambda) 
    {
        _P = create_diagonal_matrix<MatrixT>(1.0);
    }

    void
    update(std::array<double, n> current_coefficients, std::array<double, n> x, double const y_meas, double const y_calc)
    {
        VectorT K = matrix_vector_multiplication_vector_product<MatrixT, VectorT>(_P, x);
        scale_vector<VectorT>(K, 1.0 / (_lambda + vectors_multiplication_scalar_product<VectorT>(x, matrix_vector_multiplication_vector_product<MatrixT, VectorT>(_P, x))));
        
        VectorT K_epsilon_scaled = K;
        scale_vector<VectorT>(K_epsilon_scaled, y_meas - y_calc);
        _coefficients = add_vectors<VectorT>(current_coefficients, K_epsilon_scaled);

        _P = subtract_matrices<MatrixT>(_P, vectors_multiplication_matrix_product<MatrixT, VectorT>(K, vector_matrix_multiplication_vector_product<VectorT, MatrixT>(x, _P)));
        scale_matrix<MatrixT>(_P, 1.0 / _lambda);
    }

    std::array<double, n> const &
    get_coefss() const
    {
        return _coefficients;
    }
private:
    double _lambda {};
    std::array<std::array<double, n>, n> _P {};
    std::array<double, n> _coefficients {};
};