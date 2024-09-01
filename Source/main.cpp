// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "sim_objects/object.h"
#include "sim_objects/pid.h"
#include "test/test_with_plot.h"
#include "signals/signals.h"
#include "algebra/algebra.h"
#include "regression/recursive_linear_regression.h"

int main()
{
    // double const sim_time = 15.0;
    // double const time_step = 0.1;
    // TestWithPlot test(sim_time, time_step);
    // PID pid {time_step, {5.0, 1.0, 0.0}};
    // ObjectStandardRepresentation<2> object_open_loop(time_step, {1.0, 1.0, 1.0}, {0.0, 0.0});
    // ObjectStandardRepresentation<2> object_unstable(time_step, {1.0, -1.0, 1.0}, {0.0, 0.0});
    // Heaviside heaviside {};
    // Ramp ramp {};
    // Rectangle rectangle {0.0, 3.0};
    // SineWave sine_wave {0.0, 1.0, 3.14, 1.0};
    // test.test_component<PID>(pid, &ramp);
    // test.test_open_loop_control<ObjectStandardRepresentation<2>>(object_open_loop, pid, &ramp);
    // test.test_closed_loop_control<ObjectStandardRepresentation<2>>(object_unstable, pid, &ramp);
    using VectorT = std::array<double, 2>;
    using MatrixT = std::array<std::array<double, 2>, 2>;
    MatrixT diagonal = create_diagonal_matrix<MatrixT>();
    for(auto const & row : diagonal)
    {
        for(auto const & elem : row)
        {
            std::cout << elem << ", ";
        }
        std::cout << "\n";
    }

    VectorT v {1.0, 2.0};
    MatrixT m {{{1.0, 2.0}, {1.0, 2.0}}};
    VectorT out = matrix_vector_multiplication_vector_product<MatrixT, VectorT>(m, v);
    for(auto const & elem : out)
    {
        std::cout << elem << "\n";
    }

    std::cout << vectors_multiplication_scalar_product<std::array<double, 2>>(v, v) << "\n";
    scale_vector(out, 0.2);
    for(auto const & elem : out)
    {
        std::cout << elem << "\n";
    }

    VectorT adding_result = add_vectors(out, v);
    for(auto const & elem : adding_result)
    {
        std::cout << elem << "\n";
    }

    MatrixT mul_result = vectors_multiplication_matrix_product<MatrixT, VectorT>(v, v);
    for(auto const & row : mul_result)
    {
        for(auto const & elem : row)
        {
            std::cout << elem << ", ";
        }
        std::cout << "\n";
    }

    MatrixT subtract_result = subtract_matrices<MatrixT>(mul_result, m);
    for(auto const & row : subtract_result)
    {
        for(auto const & elem : row)
        {
            std::cout << elem << ", ";
        }
        std::cout << "\n";
    }

    scale_matrix<MatrixT>(subtract_result, 2.0);
    for(auto const & row : subtract_result)
    {
        for(auto const & elem : row)
        {
            std::cout << elem << ", ";
        }
        std::cout << "\n";
    }

    VectorT mul_product = vector_matrix_multiplication_vector_product<VectorT, MatrixT>(v, m);
    for(auto const & elem : mul_product)
    {
        std::cout << elem << "\n";
    }

    return 0;
}