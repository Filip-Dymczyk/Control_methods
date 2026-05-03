#include "recursive_linear_regression.h"

void
Recursive_Linear_Regression::update(VectorT const& x, double epsilon)
{
    double const eps = 1e-6;

    VectorT K {};
    matrix_vector_multiplication_vector_product(K, m_P, x);
    VectorT P_x {};
    matrix_vector_multiplication_vector_product(P_x, m_P, x);
    double const scalar = vectors_multiplication_scalar_product(x, P_x);

    double const denominator = std::max(scalar + m_lambda, eps);
    scale_vector(K, 1.0 / denominator);

    VectorT K_epsilon_scaled = K;
    scale_vector(K_epsilon_scaled, epsilon);

    VectorT new_coefficients {};
    add_vectors(new_coefficients, m_coefficients, K_epsilon_scaled);
    m_coefficients = new_coefficients;

    VectorT xT_P {};
    vector_matrix_multiplication_vector_product(xT_P, x, m_P);

    MatrixT mul_product {};
    vectors_multiplication_matrix_product(mul_product, K, xT_P);

    MatrixT new_P {};
    subtract_matrices(new_P, m_P, mul_product);
    m_P = new_P;

    scale_matrix(m_P, m_lambda);
}

Recursive_Linear_Regression::VectorT const&
Recursive_Linear_Regression::get_coefficients() const
{
    return m_coefficients;
}

void
Recursive_Linear_Regression::set_initial_coefficients(VectorT const& coefficients)
{
    m_coefficients = coefficients;
}

void
Recursive_Linear_Regression::set_lambda(double lambda)
{
    m_lambda = lambda;
}

void
Recursive_Linear_Regression::reset()
{
    m_P = {};
    create_diagonal_matrix(m_P, 1.0);
}