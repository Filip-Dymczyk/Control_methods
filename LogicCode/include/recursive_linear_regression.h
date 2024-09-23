// Author: Filip Dymczyk
// Description : RLS implementation.

#pragma once
#include <array>
#include "algebra.h"

class RecursiveLinearRegression
{
    using VectorT = std::array<double, 3u>;
    using MatrixT = std::array<std::array<double, 3u>, 3u>;
public:
    RecursiveLinearRegression(double lambda = 0.99) 
    {
        _lambda = (lambda > 0.0 && lambda <= 1.0) ? lambda : 1.0;
        create_diagonal_matrix<MatrixT>(_P , 1.0);
    }

    void
    update(VectorT const & x, double epsilon)
    {
        double const e = 10e-6;

        VectorT K {};
        matrix_vector_multiplication_vector_product<MatrixT, VectorT>(K, _P, x);
        VectorT P_x {};
        matrix_vector_multiplication_vector_product<MatrixT, VectorT>(P_x, _P, x);
        double const scalar = vectors_multiplication_scalar_product<VectorT>(x, P_x);
        
        double const denominator = std::max(scalar + _lambda, e);
        scale_vector<VectorT>(K, 1.0 / denominator);
        
        VectorT K_epsilon_scaled = K;
        scale_vector<VectorT>(K_epsilon_scaled, epsilon);
        
        VectorT new_coefficients {};
        add_vectors<VectorT>(new_coefficients, _coefficients, K_epsilon_scaled);
        _coefficients = new_coefficients;

        VectorT xT_P {};
        vector_matrix_multiplication_vector_product<VectorT, MatrixT>(xT_P, x, _P);

        MatrixT mul_product {};
        vectors_multiplication_matrix_product<MatrixT, VectorT>(mul_product, K, xT_P);

        MatrixT new_P {};
        subtract_matrices<MatrixT>(new_P, _P, mul_product);
        _P = new_P;

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