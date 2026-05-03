// Author: Filip Dymczyk
// Description : Unit tests for reset operation.

#include <gtest/gtest.h>
#include "control_system.h"
#include "object_differential_equation_representation.h"
#include "pid.h"
#include "pid_tuner.h"
#include "recursive_linear_regression.h"
#include "signals.h"
#include "test_with_plot.h"

class ResettingTest : public testing::Test, public Test_With_Plot
{
    static constexpr std::uint8_t _order = 2u;
    static constexpr double _time_step   = 0.01;
    using ObjectEquationT                = Object_Differential_Equation_Representation;

protected:
    ResettingTest() : Test_With_Plot(30.0) {}

    void
    test_closed_loop_with_resets()
    {
        Test_With_Plot::test_closed_loop_control(&_object_differential_equation_representation, &_pid, &_step);
        _object_differential_equation_representation.reset();
        _pid.reset();
        Test_With_Plot::test_closed_loop_control(&_object_differential_equation_representation, &_pid, &_step);
    }

    void
    test_tuning_with_resets()
    {
        Test_With_Plot::test_tuner(&_step, _tuner, true);
        _tuner.reset();
        _step.reset();
        Test_With_Plot::test_tuner(&_step, _tuner, true);
    }

private:
    Heaviside _step {_time_step, {5.0, 1.0}};
    PID _pid {_time_step, std::vector<double> {1.0, 1.0, 1.0}};
    ObjectEquationT _object_differential_equation_representation {
        _time_step, _order, std::vector<double> {0.0, -1.0}, std::vector<double> {2.0, 0.50}, 3.0};
    Control_System _system {
        &_object_differential_equation_representation, &_pid, Control_System::Control_Mode::CLOSED_LOOP};
    Recursive_Linear_Regression _regression {};
    Pid_Tuner _tuner {_system, _regression};
};

TEST_F(ResettingTest, ClosedLoopResetsTest) { test_closed_loop_with_resets(); }

TEST_F(ResettingTest, TunerResetsTest) { test_tuning_with_resets(); }