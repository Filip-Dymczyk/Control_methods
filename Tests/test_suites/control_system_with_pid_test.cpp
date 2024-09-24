// Author: Filip Dymczyk
// Description : Unit tests for control system - open/closed loop.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals.h"
#include "pid.h"
#include "object_differential_equation_representation.h"

class ControlSystemWithPidTest :  public testing::Test, public TestWithPlot
{   
    using Base = TestWithPlot;
    using ObjectT =  ObjectDifferentialEquationRepresentation;
    static constexpr uint8_t order = 2u;
protected:
    ControlSystemWithPidTest() : TestWithPlot(15.0) {}

    void
    test_open_loop_control()
    {
        Base::test_open_loop_control(&_object, &_pid, &_sine_wave);
    }

    void
    test_closed_loop_control()
    {
        Base::test_closed_loop_control(&_object, &_pid, &_sine_wave);
    }

private:
    double const _time_step = 0.01;
    SineWave _sine_wave {_time_step, 20.0, 5.0};
    PID _pid {_time_step, {1.0, 1.0, 1.0}};
    ObjectT _object {_time_step, order, {0.0, 0.0}, {1.0, 1.0, 1.0}};
};

TEST_F(ControlSystemWithPidTest, OpenLoopControlTest)
{
    test_open_loop_control();
}

TEST_F(ControlSystemWithPidTest, ClosedLoopControlTest)
{
    test_closed_loop_control();
}