// Author: Filip Dymczyk
// Description : Unit tests for algebra operations.

#include <gtest/gtest.h>
#include <array>
#include "algebra.h"

class AlgebraTest : public testing::Test
{
    using VectorT = std::array<double, 2>;
    using MatrixT = std::array<std::array<double, 2>, 2>;

    VectorT const test_vectorA {1.0, 2.0};
    MatrixT const test_matrixA {{{1.0, 2.0}, {1.0, 2.0}}};
    MatrixT const test_matrixB {{{-1.0, 3.0}, {4.0, 1.0}}};
protected:
    void
    check_diagonal_matrix() const 
    {
        double const scalar = 2.0;
        MatrixT out {};
        create_diagonal_matrix<MatrixT>(out, scalar);

        float const zero = 0.0f;
        for(std::size_t i = 0; i < out.size(); i++)
        {
            for(std::size_t j = 0; j < out[0].size(); j++)
            {
                if(i == j)
                {
                    EXPECT_FLOAT_EQ(cast_to_float(scalar), cast_to_float(out[i][j]));
                }
                else
                {
                    EXPECT_FLOAT_EQ(zero, cast_to_float(out[i][j]));
                } 
            }
        }
    }

    void
    check_matrix_vector_multiplication_vector_product() const
    {
        VectorT out {};
        matrix_vector_multiplication_vector_product<MatrixT, VectorT>(out, test_matrixA, test_vectorA);
        VectorT const expected_out {5.0, 5.0};
        check_vector_values(expected_out, out);
    }

    void
    check_vectors_multiplication_scalar_product() const
    {
        double const out = vectors_multiplication_scalar_product<VectorT>(test_vectorA, test_vectorA);
        float const expected_out = 5.0f;
        EXPECT_FLOAT_EQ(expected_out, cast_to_float(out));
    }

    void
    check_vector_scaling() const 
    {
        double const scaler = 2.0;
        VectorT out = test_vectorA;
        scale_vector<VectorT>(out, scaler);
        VectorT const expected_out {2.0, 4.0};
        check_vector_values(expected_out, out);
    }

    void
    check_vectors_addition() const 
    {
        VectorT out {};
        add_vectors<VectorT>(out, test_vectorA, test_vectorA);
        VectorT const expected_out {2.0, 4.0};
        check_vector_values(expected_out, out);
    }

    void
    check_vectors_multiplication_matrix_product() const
    {
        MatrixT out {};
        vectors_multiplication_matrix_product<MatrixT, VectorT>(out, test_vectorA, test_vectorA);
        MatrixT const expected_out {{{1.0, 2.0}, {2.0, 4.0}}};
        check_matrix_values(expected_out, out);
    }

    void
    check_matrices_subtraction() const
    {
        MatrixT out {};
        subtract_matrices<MatrixT>(out, test_matrixA, test_matrixB);
        MatrixT const expected_out {{{2.0, -1.0}, {-3.0, 1.0}}};
        check_matrix_values(expected_out, out);
    }

    void
    check_matrix_scaling() const 
    {
        double const scaler = 2.0;
        MatrixT out = test_matrixA;
        scale_matrix<MatrixT>(out, scaler);
        MatrixT const expected_out {{{2.0, 4.0}, {2.0, 4.0}}};
        check_matrix_values(expected_out, out);
    }

    void
    check_vector_matrix_multiplication_vector_product() const
    {
        VectorT out {};
        vector_matrix_multiplication_vector_product<VectorT, MatrixT>(out, test_vectorA, test_matrixA);
        VectorT const expected_out {3.0, 6.0};
        check_vector_values(expected_out, out);
    }

private:
    float
    cast_to_float(double scalar) const 
    {
        return static_cast<float>(scalar);
    }

    void
    check_vector_values(VectorT const & expected_out, VectorT const & out) const 
    {
        for(std::size_t i = 0; i < out.size(); i++)
        {
            EXPECT_FLOAT_EQ(cast_to_float(expected_out[i]), cast_to_float(out[i]));
        }
    }

    void
    check_matrix_values(MatrixT const & expected_out, MatrixT const & out) const 
    {
        for(std::size_t i = 0; i < out.size(); i++)
        {
            for(std::size_t j = 0; j < out[0].size(); j++)
            {
                EXPECT_FLOAT_EQ(cast_to_float(expected_out[i][j]), cast_to_float(out[i][j]));
            }
        }
    }
};      

TEST_F(AlgebraTest, CreateDiagonalMatrixTest) 
{
    check_diagonal_matrix();
}  

TEST_F(AlgebraTest, MatrixVectorMultiplicationVectorProductTest)
{
    check_matrix_vector_multiplication_vector_product();
}

TEST_F(AlgebraTest, VectorsMultiplicationScalarProductTest)
{
    check_vectors_multiplication_scalar_product();
}

TEST_F(AlgebraTest, VectorScalingTest)
{
    check_vector_scaling();
}

TEST_F(AlgebraTest, VectorsAdditionTest)
{
    check_vectors_addition();
}

TEST_F(AlgebraTest, VectorsMultiplicationMatrixProductTest)
{
    check_vectors_multiplication_matrix_product();
}

TEST_F(AlgebraTest, MatricesSubtractionTest)
{
    check_matrices_subtraction();
}

TEST_F(AlgebraTest, MatrixScalingTest)
{
    check_matrix_scaling();
}

TEST_F(AlgebraTest, VectorMatrixMultiplicationVectorProductTest)
{
    check_vector_matrix_multiplication_vector_product();
}