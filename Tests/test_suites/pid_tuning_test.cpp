// Author: Filip Dymczyk
// Description : Unit tests for pid tuning operation.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals.h"
#include "pid.h"
#include "object_differential_equation_representation.h"
#include "object_state_space_representation.h"
#include "control_system.h"
#include "recursive_linear_regression.h"
#include "pid_tuner.h"


class PidTuningTest :  public testing::Test, public Test_With_Plot
{   
    static constexpr std::uint8_t _order = 2u;
    static constexpr double _time_step = 0.01;
    using ObjectEquationT =  Object_Differential_Equation_Representation;
    using ObjectStateSpaceT =  Object_State_Space_Representation;
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
    Sine_Wave _sine_wave_1 {_time_step, 1.0, 1.0, {}};
    PID _pid_1 {_time_step, {}};
    ObjectEquationT _object_differential_equation_representation {_time_step, _order, {0.0, 0.0}, {2.0, 0.50, 3.0}};
    Control_System _system_1 {&_object_differential_equation_representation, &_pid_1, Control_System::Control_Mode::CLOSED_LOOP};
    Pid_Tuner _tuner_1 {_system_1, {}};

    Sine_Wave _sine_wave_2 {_time_step, 1.0, 1.0, {}};
    PID _pid_2 {_time_step, {}};
    ObjectStateSpaceT _object_state_space_representation {_time_step, _order, {0.0, 0.0}, {{{0.0, 1.0}, {-0.5, -2.0}}}, {0.0, 3.0}, {1.0, 0.0}};
    Control_System _system_2 {&_object_state_space_representation, &_pid_2, Control_System::Control_Mode::CLOSED_LOOP};
    Pid_Tuner _tuner_2 {_system_2, {}};
};

TEST_F(PidTuningTest, TunerWithObjectRepresentedByDifferentialEquationTest)
{
    test_tuner_object_differential_equation_representation();
}

TEST_F(PidTuningTest, TunerWithObjectRepresentedByStateSpaceTest)
{
    test_tuner_object_state_space_representation();
}