// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "sim_objects/object.h"
#include "sim_objects/pid.h"
#include "algebra/algebra.h"
#include "regression/recursive_linear_regression.h"
#include "tuner/tuner.h"

int main()
{
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