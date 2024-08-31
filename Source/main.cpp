// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "sim_objects/object.h"
#include "sim_objects/pid.h"
#include "test_with_plot.h"
#include "signals/signals.h"

int main()
{
    double const sim_time = 15.0;
    double const time_step = 0.1;
    TestWithPlot test(sim_time, time_step);
    PID pid {time_step, {5.0, 1.0, 0.0}};
    ObjectStandardRepresentation<2> object_open_loop(time_step, {1.0, 1.0, 1.0}, {0.0, 0.0});
    ObjectStandardRepresentation<2> object_unstable(time_step, {1.0, -1.0, 1.0}, {0.0, 0.0});
    Heaviside heaviside {};
    test.test_component(pid);
    test.test_open_loop_control<ObjectStandardRepresentation<2>, Heaviside>(object_open_loop, pid, heaviside);
    test.test_closed_loop_control<ObjectStandardRepresentation<2>, Heaviside>(object_unstable, pid, heaviside);
    return 0;
}