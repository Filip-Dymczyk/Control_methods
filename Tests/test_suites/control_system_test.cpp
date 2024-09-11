// Author: Filip Dymczyk
// Description : Unit tests for individual components with sine wave signal as an input.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals/signals.h"
#include "sim_objects/pid.h"
#include "sim_objects/object.h"

static constexpr uint8_t order = 2u;
class ControlSystemTest :  public testing::Test, public TestWithPlot
{   
    using Base = TestWithPlot;
    using ObjectT =  ObjectStandardRepresentation<order>;
protected:
    ControlSystemTest() : TestWithPlot(15.0) {}

    void
    test_open_loop_control()
    {
        Base::test_open_loop_control<ObjectT, PID>(object, pid, &sine_wave);
    }

    void
    test_closed_loop_control()
    {
        Base::test_closed_loop_control<ObjectT, PID>(object, pid, &sine_wave);
    }

private:
    double const _time_step = 0.01;
    SineWave sine_wave {_time_step, 20.0, 5.0};
    PID pid {_time_step, {1.0, 1.0, 1.0}};
    ObjectT object {_time_step, {1.0, 1.0, 1.0}, {0.0, 0.0}};
};

TEST_F(ControlSystemTest, OpenLoopControlTest)
{
    test_open_loop_control();
}

TEST_F(ControlSystemTest, ClosedLoopControlTest)
{
    test_closed_loop_control();
}