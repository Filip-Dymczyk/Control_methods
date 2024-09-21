// Author: Filip Dymczyk
// Description : Basic algebra operations.

#pragma once
#include <assert.h>

template<typename MatrixT>
MatrixT
create_diagonal_matrix(double scalar)
{   
    MatrixT out_matrix {};
    
    assert(out_matrix.size());
    assert(out_matrix.size());

    for(std::size_t i = 0; i < out_matrix.size(); i++)
    {
        out_matrix[i][i] = scalar;
    }

    return out_matrix;
}

template<typename MatrixT, typename VectorT>
VectorT
matrix_vector_multiplication_vector_product(MatrixT const & matrix, VectorT const & vector)
{
    assert(matrix.size());
    assert(matrix[0].size());
    assert(vector.size());
    assert(matrix[0].size() == vector.size());

    VectorT out_vector {};

    assert(matrix.size() == out_vector.size());

    for(std::size_t i = 0; i < matrix.size(); i++)
    {
        double row_value {};
        for(std::size_t j = 0; j < matrix[0].size(); j++)
        {
            row_value += matrix[i][j] * vector[j];
        }
        out_vector[i] = row_value;
    }

    return out_vector;
}

template<typename VectorT>
double 
vectors_multiplication_scalar_product(VectorT const & vector_T, VectorT const & vector)
{
    assert(vector_T.size());

    double out_scalar {};

    for(std::size_t i = 0; i < vector_T.size(); i++)
    {
        out_scalar += vector_T[i] * vector[i];
    }

    return out_scalar;
}

template<typename VectorT>
void
scale_vector(VectorT & vector, double scaler)
{
    assert(vector.size());

    for(std::size_t i = 0; i < vector.size(); i++)
    {
        vector[i] = vector[i] * scaler;
    }
}

template<typename VectorT>
VectorT
add_vectors(VectorT const & v_lhs, VectorT const & v_rhs)
{
    assert(v_lhs.size());

    VectorT out_vector {};
    
    for(std::size_t i = 0; i < v_lhs.size(); i++)
    {
        out_vector[i] = v_lhs[i] + v_rhs[i];
    }

    return out_vector;
}

template<typename MatrixT, typename VectorT>
MatrixT
vectors_multiplication_matrix_product(VectorT const & v_lhs, VectorT const & v_rhs)
{
    assert(v_lhs.size());

    MatrixT out_matrix {};

    assert(out_matrix.size() == v_lhs.size());
    assert(out_matrix[0].size() == v_rhs.size());

    for(std::size_t i = 0; i < v_lhs.size(); i++)
    {
        for(std::size_t j = 0; j < v_rhs.size(); j++)
        {
            out_matrix[i][j] = v_lhs[i] * v_rhs[j];
        }
    }

    return out_matrix;
}

template<typename MatrixT>
MatrixT 
subtract_matrices(MatrixT const & m_lhs, MatrixT const & m_rhs)
{
    assert(m_lhs.size());
    assert(m_lhs[0].size());

    MatrixT out_matrix {};

    for(std::size_t i = 0; i < m_lhs.size(); i++)
    {
        for(std::size_t j = 0; j < m_rhs[0].size(); j++)
        {
            out_matrix[i][j] = m_lhs[i][j] - m_rhs[i][j];
        }
    }

    return out_matrix;
}

template<typename MatrixT>
void
scale_matrix(MatrixT & matrix, double scaler)
{
    assert(matrix.size());
    assert(matrix[0].size());

    for(std::size_t i = 0; i < matrix.size(); i++)
    {
        for(std::size_t j = 0; j < matrix[0].size(); j++)
        {
            matrix[i][j] *= scaler;
        }
    }
}

template<typename VectorT, typename MatrixT>
VectorT
vector_matrix_multiplication_vector_product(VectorT const & vector_T, MatrixT const & matrix)
{  
    assert(vector_T.size());
    assert(matrix.size());
    assert(matrix[0].size());
    assert(vector_T.size() == matrix.size());

    VectorT out_vector {};

    for(std::size_t i = 0; i < vector_T.size(); i++)
    {
        double column_value {};
        for(std::size_t j = 0; j < matrix.size(); j++)
        {
            column_value += vector_T[j] * matrix[j][i];
        }
        out_vector[i] = column_value;
    }

    return out_vector;
}