// Author: Filip Dymczyk
// Description : Unit tests for reset operation.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "include/signals.h"
#include "include/pid.h"
#include "include/object_differential_equation_representation.h"
#include "include/control_system.h"
#include "include/recursive_linear_regression.h"
#include "include/pid_tuner.h"

class ResettingTest :  public testing::Test, public TestWithPlot
{   
    static constexpr std::uint8_t _order = 2u;
    static constexpr double _time_step = 0.01;
    using Base = TestWithPlot;
    using ObjectEquationT =  ObjectDifferentialEquationRepresentation;
protected:
    ResettingTest() : TestWithPlot(30.0) {}

    void
    test_closed_loop_with_resets()
    {
        Base::test_closed_loop_control(&_object_differential_equation_representation, &_pid, &_step);
        _object_differential_equation_representation.reset();
        _pid.reset();
        Base::test_closed_loop_control(&_object_differential_equation_representation, &_pid, &_step);
    }

    void
    test_tuning_with_resets()
    {
        Base::test_tuner<PidTuner>(&_step, _tuner, true);
        _tuner.reset();
        _step.reset();
        Base::test_tuner<PidTuner>(&_step, _tuner, true);
    }
private:
    Heaviside _step {_time_step, {5.0, 1.0}};
    PID _pid {_time_step, {1.0, 1.0, 1.0}};
    ObjectEquationT _object_differential_equation_representation {_time_step, _order, {0.0, -1.0}, {2.0, 0.50, 3.0}};
    ControlSystem _system {&_object_differential_equation_representation, &_pid, ControlMode::CLOSED_LOOP};
    RecursiveLinearRegression _regression {};
    PidTuner _tuner {_system, _regression};
};

TEST_F(ResettingTest, ClosedLoopResetsTest)
{
    test_closed_loop_with_resets();
}

TEST_F(ResettingTest, TunerResetsTest)
{
    test_tuning_with_resets();
}