// Author: Filip Dymczyk
// Description : Unit tests for control system - open/closed loop.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals.h"
#include "two_position_controller.h"
#include "object_differential_equation_representation.h"

static constexpr uint8_t order = 2u;
class ControlSystemWithTwoPositionControllerTest :  public testing::Test, public TestWithPlot
{   
    using Base = TestWithPlot;
    using ObjectT =  ObjectDifferentialEquationRepresentation;
protected:
    ControlSystemWithTwoPositionControllerTest() : TestWithPlot(15.0) {}

    void
    test_open_loop_control()
    {
        Base::test_open_loop_control(&_object, &_two_position_controller, &_pulse, true);
    }

    void
    test_closed_loop_control()
    {
        Base::test_closed_loop_control(&_object, &_two_position_controller, &_pulse, true);
    }

private:
    double const _time_step = 0.01;
    PulseWave _pulse {_time_step, 0.75, 4.0, {}};
    TwoPositionController _two_position_controller {_time_step, {0.0, 1.0, 1.0}};
    ObjectT _object {_time_step, order, {0.0, 0.0}, {1.0, 1.0, 1.0}};
};

TEST_F(ControlSystemWithTwoPositionControllerTest, OpenLoopControlTest)
{
    test_open_loop_control();
}

TEST_F(ControlSystemWithTwoPositionControllerTest, ClosedLoopControlTest)
{
    test_closed_loop_control();
}