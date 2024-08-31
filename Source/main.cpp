// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "sim_objects/object.h"
#include "sim_objects/pid.h"
#include "test_with_plot.h"
#include "signals/signals.h"
#include "algebra/algebra.h"

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
    std::array<double, 2> v {1.0, 2.0};
    std::array<std::array<double, 2>, 2> m {{{1.0, 2.0}, {1.0, 2.0}}};
    std::array<double, 2> out = matrix_vector_vector_product<std::array<std::array<double, 2>, 2>, std::array<double, 2>>(m, v);
    for(auto const & elem : out)
    {
        std::cout << elem << "\n";
    }

    std::cout << vector_vector_scalar_product<std::array<double, 2>>(v, v);
    return 0;
}