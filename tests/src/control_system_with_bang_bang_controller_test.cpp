// Author: Filip Dymczyk
// Description : Unit tests for control system - open/closed loop.

#include <gtest/gtest.h>
#include "bang_bang_controller.h"
#include "object_differential_equation_representation.h"
#include "signals.h"
#include "test_with_plot.h"

static constexpr uint8_t order = 2u;

class ControlSystemWithBangBangControllerTest : public testing::Test, public Test_With_Plot
{
    using ObjectT = Object_Differential_Equation_Representation;

protected:
    ControlSystemWithBangBangControllerTest() : Test_With_Plot(15.0) {}

    void
    test_open_loop_control()
    {
        Test_With_Plot::test_open_loop_control(&m_object, &m_bang_bang_controller, &m_pulse, true);
    }

    void
    test_closed_loop_control()
    {
        Test_With_Plot::test_closed_loop_control(&m_object, &m_bang_bang_controller, &m_pulse, true);
    }

private:
    double const m_time_step = 0.01;
    Pulse_Wave m_pulse {m_time_step, 0.75, 4.0, {}};
    Bang_Bang_Controller m_bang_bang_controller {m_time_step, {0.0, 1.0, 1.0}};
    ObjectT m_object {m_time_step, order, std::vector<double> {0.0, 0.0}, std::vector<double> {1.0, 1.0}, 1.0};
};

TEST_F(ControlSystemWithBangBangControllerTest, OpenLoopControlTest) { test_open_loop_control(); }

TEST_F(ControlSystemWithBangBangControllerTest, ClosedLoopControlTest) { test_closed_loop_control(); }