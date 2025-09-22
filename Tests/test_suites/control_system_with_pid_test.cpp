// Author: Filip Dymczyk
// Description : Unit tests for control system - open/closed loop.

#include <gtest/gtest.h>
#include <memory>
#include "object_differential_equation_representation.h"
#include "pid.h"
#include "signals.h"
#include "test_with_plot.h"

class ControlSystemWithPidTest : public testing::Test, public Test_With_Plot
{
    using ObjectT                  = Object_Differential_Equation_Representation;
    static constexpr uint8_t order = 2u;

protected:
    ControlSystemWithPidTest() : Test_With_Plot(15.0) {}

    void
    test_open_loop_control()
    {
        Test_With_Plot::test_open_loop_control(_object, _pid, &_sine_wave);
    }

    void
    test_closed_loop_control()
    {
        Test_With_Plot::test_closed_loop_control(_object, _pid, &_sine_wave);
    }

private:
    double const _time_step = 0.01;
    Sine_Wave _sine_wave {_time_step, 20.0, 5.0, {}};
    std::shared_ptr<PID> _pid        = std::make_shared<PID>(_time_step, std::vector<double> {1.0, 1.0, 1.0});
    std::shared_ptr<ObjectT> _object = std::make_shared<ObjectT>(
        _time_step, order, std::vector<double> {0.0, 0.0}, std::vector<double> {1.0, 1.0}, 1.0);
};

TEST_F(ControlSystemWithPidTest, OpenLoopControlTest) { test_open_loop_control(); }

TEST_F(ControlSystemWithPidTest, ClosedLoopControlTest) { test_closed_loop_control(); }