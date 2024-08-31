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
    Ramp ramp {};
    Rectangle rectangle {0.0, 3.0};
    test.test_component(pid, ramp);
    test.test_open_loop_control<ObjectStandardRepresentation<2>, Rectangle>(object_open_loop, pid, rectangle);
    test.test_closed_loop_control<ObjectStandardRepresentation<2>, Rectangle>(object_unstable, pid, rectangle);
    return 0;
}