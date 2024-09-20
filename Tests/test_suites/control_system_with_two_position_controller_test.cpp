// Author: Filip Dymczyk
// Description : Unit tests for control system - open/closed loop.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals/signals.h"
#include "sim_objects/two_position_controller.h"
#include "sim_objects/object.h"

static constexpr uint8_t order = 2u;
class ControlSystemWithTwoPositionControllerTest :  public testing::Test, public TestWithPlot
{   
    using Base = TestWithPlot;
    using ObjectT =  ObjectStandardRepresentation<order>;
protected:
    ControlSystemWithTwoPositionControllerTest() : TestWithPlot(15.0) {}

    void
    test_open_loop_control()
    {
        Base::test_open_loop_control<ObjectT, TwoPositionController>(object, two_position_controller, &rect, true);
    }

    void
    test_closed_loop_control()
    {
        Base::test_closed_loop_control<ObjectT, TwoPositionController>(object, two_position_controller, &rect, true);
    }

private:
    double const _time_step = 0.01;
    Rectangle rect {_time_step, 10.0};
    TwoPositionController two_position_controller {_time_step, {0.0, 1.0, 1.0}};
    ObjectT object {_time_step, {1.0, 1.0, 1.0}, {0.0, 0.0}};
};

TEST_F(ControlSystemWithTwoPositionControllerTest, OpenLoopControlTest)
{
    test_open_loop_control();
}

TEST_F(ControlSystemWithTwoPositionControllerTest, ClosedLoopControlTest)
{
    test_closed_loop_control();
}