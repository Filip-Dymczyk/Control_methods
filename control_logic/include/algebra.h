// Author: Filip Dymczyk
// Description : Basic algebra operations.

#pragma once
#include <cassert>
#include <cstdlib>

template<typename MatrixT>
void
create_diagonal_matrix(MatrixT& out_matrix, double scalar)
{
    assert(out_matrix.size());
    assert(out_matrix.at(0).size());

    for(std::size_t i = 0; i < out_matrix.size(); i++)
    {
        out_matrix.at(i).at(i) = scalar;
    }
}

template<typename MatrixT, typename VectorT>
void
matrix_vector_multiplication_vector_product(VectorT& out_vector, MatrixT const& matrix, VectorT const& vector)
{
    assert(matrix.size());
    assert(matrix.at(0).size());
    assert(matrix.at(0).size() == vector.size());
    assert(out_vector.size() == matrix.size());

    for(std::size_t i = 0; i < matrix.size(); i++)
    {
        double row_value {};
        for(std::size_t j = 0; j < matrix.at(0).size(); j++)
        {
            row_value += matrix.at(i).at(j) * vector.at(j);
        }
        out_vector.at(i) = row_value;
    }
}

template<typename VectorT>
double
vectors_multiplication_scalar_product(VectorT const& vector_T, VectorT const& vector)
{
    assert(vector_T.size());
    assert(vector_T.size() == vector.size());
    double out_scalar {};

    for(std::size_t i = 0; i < vector_T.size(); i++)
    {
        out_scalar += vector_T.at(i) * vector.at(i);
    }

    return out_scalar;
}

template<typename VectorT>
void
scale_vector(VectorT& vector, double scaler)
{
    assert(vector.size());

    for(std::size_t i = 0; i < vector.size(); i++)
    {
        vector.at(i) *= scaler;
    }
}

template<typename VectorT>
void
add_vectors(VectorT& out_vector, VectorT const& v_lhs, VectorT const& v_rhs)
{
    assert(v_lhs.size());
    assert(v_lhs.size() == v_rhs.size());
    assert(out_vector.size() == v_lhs.size());

    for(std::size_t i = 0; i < v_lhs.size(); i++)
    {
        out_vector.at(i) = v_lhs.at(i) + v_rhs.at(i);
    }
}

template<typename MatrixT, typename VectorT>
void
vectors_multiplication_matrix_product(MatrixT& out_matrix, VectorT const& v_lhs, VectorT const& v_rhs)
{
    assert(v_lhs.size());
    assert(v_lhs.size() == v_rhs.size());
    assert(out_matrix.size() == v_lhs.size());
    assert(out_matrix.at(0).size() == v_rhs.size());

    for(std::size_t i = 0; i < v_lhs.size(); i++)
    {
        for(std::size_t j = 0; j < v_rhs.size(); j++)
        {
            out_matrix.at(i).at(j) = v_lhs.at(i) * v_rhs.at(j);
        }
    }
}

template<typename MatrixT>
void
subtract_matrices(MatrixT& out_matrix, MatrixT const& m_lhs, MatrixT const& m_rhs)
{
    assert(m_lhs.size());
    assert(m_lhs.at(0).size());
    assert(m_lhs.size() == m_rhs.size());
    assert(m_lhs.at(0).size() == m_rhs.at(0).size());
    assert(out_matrix.size() == m_lhs.size());
    assert(out_matrix.at(0).size() == m_lhs.at(0).size());

    for(std::size_t i = 0; i < m_lhs.size(); i++)
    {
        for(std::size_t j = 0; j < m_rhs.at(0).size(); j++)
        {
            out_matrix.at(i).at(j) = m_lhs.at(i).at(j) - m_rhs.at(i).at(j);
        }
    }
}

template<typename MatrixT>
void
scale_matrix(MatrixT& matrix, double scaler)
{
    assert(matrix.size());
    assert(matrix.at(0).size());

    for(std::size_t i = 0; i < matrix.size(); i++)
    {
        for(std::size_t j = 0; j < matrix.at(0).size(); j++)
        {
            matrix.at(i).at(j) *= scaler;
        }
    }
}

template<typename VectorT, typename MatrixT>
void
vector_matrix_multiplication_vector_product(VectorT& out_vector, VectorT const& vector_T, MatrixT const& matrix)
{
    assert(vector_T.size());
    assert(matrix.size());
    assert(matrix.at(0).size());
    assert(vector_T.size() == matrix.size());
    assert(out_vector.size() == vector_T.size());

    for(std::size_t i = 0; i < vector_T.size(); i++)
    {
        double column_value {};
        for(std::size_t j = 0; j < matrix.size(); j++)
        {
            column_value += vector_T.at(j) * matrix.at(j).at(i);
        }
        out_vector.at(i) = column_value;
    }
}