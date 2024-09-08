// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "sim_objects/object.h"
#include "sim_objects/pid.h"
#include "test/test_with_plot.h"
#include "signals/signals.h"
#include "algebra/algebra.h"
#include "regression/recursive_linear_regression.h"
#include "tuner/tuner.h"

int main()
{
    // double const sim_time = 15.0;
    // double const time_step = 0.1;
    // TestWithPlot test(sim_time);
    // PID pid {time_step, {5.0, 1.0, 0.0}};
    // ObjectStandardRepresentation<2> object_open_loop(time_step, {1.0, 1.0, 1.0}, {0.0, 0.0});
    // ObjectStandardRepresentation<2> object_unstable(time_step, {1.0, -1.0, 1.0}, {0.0, 0.0});
    // ObjectStandardRepresentation<2> object_test(time_step, {1.0, -1.0, 1.0}, {0.0, 0.0});
    // Heaviside heaviside {time_step};
    // Ramp ramp {time_step};
    // Rectangle rectangle {time_step, 3.0};
    // SineWave sine_wave {time_step, 3.14, 1.0};
    // test.test_component<PID>(pid, &heaviside);
    // test.test_open_loop_control<ObjectStandardRepresentation<2>>(object_open_loop, pid, &ramp);
    // test.test_closed_loop_control<ObjectStandardRepresentation<2>>(object_unstable, pid, &rectangle);
    // test.test_closed_loop_control<ObjectStandardRepresentation<2>>(object_test, pid, &sine_wave);
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
    // RecursiveLinearRegression<2> regression(2.0);
    // regression.update({1.0, 1.0}, {1.0, 2.0}, 1.0);
    using Object = ObjectStandardRepresentation<2>;
    using ControlSystemT = ControlSystem<Object, PID>;
    using RegressionT = RecursiveLinearRegression<3>;
    using TunerT = Tuner<ControlSystemT, RegressionT>;
    double const sim_time = 30.0;
    double const time_step = 0.1;
    TestWithPlot test(sim_time);
    
    PID pid_1 {time_step, {0.25, 1.0, 0.3}};
    Object object_1(time_step, {2.0, 0.50, 3.0}, {0.0, 0.0});
    SineWave sine_wave_1 {time_step, 0.5, 1.0};
    
    PID pid_2 {time_step, {0.25, 1.0, 0.3}};
    Object object_2(time_step, {2.0, 0.50, 3.0}, {0.0, 0.0});
    ControlSystemT control_system {object_2, pid_2, ControlMode::CLOSED_LOOP};
    SineWave sine_wave_2 {time_step, 0.5, 1.0};
    
    RegressionT regression {};
    
    TunerT tuner {&sine_wave_2, control_system, regression};
    test.test_closed_loop_control<Object>(object_1, pid_1, &sine_wave_1);
    test.test_tuner<TunerT>(tuner);
    return 0;
}