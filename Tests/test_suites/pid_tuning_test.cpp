// Author: Filip Dymczyk
// Description : Unit tests for pid tuning operation.

#include <gtest/gtest.h>
#include "control_system.h"
#include "object_differential_equation_representation.h"
#include "object_state_space_representation.h"
#include "pid.h"
#include "pid_tuner.h"
#include "recursive_linear_regression.h"
#include "signals.h"
#include "test_with_plot.h"

class PidTuningTest : public testing::Test, public Test_With_Plot
{
    static constexpr std::uint8_t order = 2u;
    static constexpr double time_step   = 0.01;
    using ObjectEquationT               = Object_Differential_Equation_Representation;
    using ObjectStateSpaceT             = Object_State_Space_Representation;

protected:
    PidTuningTest() : Test_With_Plot(30.0) {}

    void
    test_tuner_object_differential_equation_representation()
    {
        Test_With_Plot::test_tuner<Pid_Tuner>(&_sine_wave_1, _tuner_1);
    }

    void
    test_tuner_object_state_space_representation()
    {
        Test_With_Plot::test_tuner<Pid_Tuner>(&_sine_wave_2, _tuner_2);
    }

private:
    Sine_Wave _sine_wave_1 {time_step, 1.0, 1.0, {}};
    std::shared_ptr<PID> pid_1 = std::make_shared<PID>(time_step, std::vector<double> {0.0, 0.0, 0.0});
    ObjectEquationT object_differential_equation_representation {time_step, order, {0.0, 0.0}, {2.0, 0.50, 3.0}};
    Control_System system_1 {
        &object_differential_equation_representation, pid_1, Control_System::Control_Mode::CLOSED_LOOP};
    Pid_Tuner _tuner_1 {system_1, {}};

    Sine_Wave _sine_wave_2 {time_step, 1.0, 1.0, {}};
    std::shared_ptr<PID> pid_2 = std::make_shared<PID>(time_step, std::vector<double> {0.0, 0.0, 0.0});
    ObjectStateSpaceT object_state_space_representation {
        time_step, order, {0.0, 0.0}, {{{0.0, 1.0}, {-0.5, -2.0}}}, {0.0, 3.0}, {1.0, 0.0}};
    Control_System system_2 {&object_state_space_representation, pid_2, Control_System::Control_Mode::CLOSED_LOOP};
    Pid_Tuner _tuner_2 {system_2, {}};
};

TEST_F(PidTuningTest, TunerWithObjectRepresentedByDifferentialEquationTest)
{
    test_tuner_object_differential_equation_representation();
}

TEST_F(PidTuningTest, TunerWithObjectRepresentedByStateSpaceTest) { test_tuner_object_state_space_representation(); }