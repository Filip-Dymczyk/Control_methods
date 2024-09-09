// Author: Filip Dymczyk
// Description : Unit tests for algebra operations.

#include <gtest/gtest.h>
#include <array>
#include "algebra/algebra.h"

class AlgebraTest : public testing::Test
{
protected:
    using VectorT = std::array<double, 2>;
    using MatrixT = std::array<std::array<double, 2>, 2>;

    VectorT test_vectorA {1.0, 2.0};
    MatrixT test_vectorB {1.0, 2.0};

    void
    check_diagonal_matrix(MatrixT const & matrix, double scalar)
    {
        for(std::size_t i = 0; i < matrix.size(); i++)
        {
            for(std::size_t j = 0; j < matrix[0].size(); j++)
            {
                if(i == j)
                {
                    EXPECT_FLOAT_EQ(scalar, matrix[i][j]);
                }
                else
                {
                    EXPECT_FLOAT_EQ(0.0, matrix[i][j]);
                } 
            }
        }
    }
};      

TEST_F(AlgebraTest, CreateDiagonalMatrixTest) 
{
    double scalar = 2.0;
    MatrixT diagonal = create_diagonal_matrix<MatrixT>(scalar);
    check_diagonal_matrix(diagonal, scalar);
}       

// using VectorT = std::array<double, 2>;
    // using MatrixT = std::array<std::array<double, 2>, 2>;
    // MatrixT diagonal = create_diagonal_matrix<MatrixT>();
    // for(auto const & row : diagonal)
    // {
    //     for(auto const & elem : row)
    //     {
    //         std::cout << elem << ", ";
    //     }
    //     std::cout << "\n";
    // }

    // VectorT v {1.0, 2.0};
    // MatrixT m {{{1.0, 2.0}, {1.0, 2.0}}};
    // VectorT out = matrix_vector_multiplication_vector_product<MatrixT, VectorT>(m, v);
    // for(auto const & elem : out)
    // {
    //     std::cout << elem << "\n";
    // }

    // std::cout << vectors_multiplication_scalar_product<std::array<double, 2>>(v, v) << "\n";
    // scale_vector(out, 0.2);
    // for(auto const & elem : out)
    // {
    //     std::cout << elem << "\n";
    // }

    // VectorT adding_result = add_vectors(out, v);
    // for(auto const & elem : adding_result)
    // {
    //     std::cout << elem << "\n";
    // }

    // MatrixT mul_result = vectors_multiplication_matrix_product<MatrixT, VectorT>(v, v);
    // for(auto const & row : mul_result)
    // {
    //     for(auto const & elem : row)
    //     {
    //         std::cout << elem << ", ";
    //     }
    //     std::cout << "\n";
    // }

    // MatrixT subtract_result = subtract_matrices<MatrixT>(mul_result, m);
    // for(auto const & row : subtract_result)
    // {
    //     for(auto const & elem : row)
    //     {
    //         std::cout << elem << ", ";
    //     }
    //     std::cout << "\n";
    // }

    // scale_matrix<MatrixT>(subtract_result, 2.0);
    // for(auto const & row : subtract_result)
    // {
    //     for(auto const & elem : row)
    //     {
    //         std::cout << elem << ", ";
    //     }
    //     std::cout << "\n";
    // }

    // VectorT mul_product = vector_matrix_multiplication_vector_product<VectorT, MatrixT>(v, m);
    // for(auto const & elem : mul_product)
    // {
    //     std::cout << elem << "\n";
    // }
