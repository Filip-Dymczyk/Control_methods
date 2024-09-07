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
    RecursiveLinearRegression(double const lambda = 0.99) 
    {
        if(lambda > 1.0 || lambda < 0.0)
        {
            lambda = 1.0;
        }
        _lambda = lambda;
        _P = create_diagonal_matrix<MatrixT>(1.0);
    }

    void
    update(VectorT const & x, double const epsilon)
    {
        VectorT K = matrix_vector_multiplication_vector_product<MatrixT, VectorT>(_P, x);
        scale_vector<VectorT>(K, 1.0 / (_lambda + vectors_multiplication_scalar_product<VectorT>(x, matrix_vector_multiplication_vector_product<MatrixT, VectorT>(_P, x))));
        
        VectorT K_epsilon_scaled = K;
        scale_vector<VectorT>(K_epsilon_scaled, epsilon);
        _coefficients = add_vectors<VectorT>(_coefficients, K_epsilon_scaled);

        _P = subtract_matrices<MatrixT>(_P, vectors_multiplication_matrix_product<MatrixT, VectorT>(K, vector_matrix_multiplication_vector_product<VectorT, MatrixT>(x, _P)));
        scale_matrix<MatrixT>(_P, _lambda);
    }

    VectorT const &
    get_coeffs() const
    {
        return _coefficients;
    }
private:
    double _lambda {};
    MatrixT _P {};
    VectorT _coefficients {};
};