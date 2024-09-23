// Author: Filip Dymczyk
// Description : Unit tests for pid tuning operation.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "include/signals.h"
#include "include/pid.h"
#include "include/object_differential_equation_representation.h"
#include "include/object_state_space_representation.h"
#include "include/control_system.h"
#include "include/recursive_linear_regression.h"
#include "include/pid_tuner.h"


class PidTuningTest :  public testing::Test, public TestWithPlot
{   
    static constexpr std::uint8_t _order = 2u;
    static constexpr double _time_step = 0.01;
    using Base = TestWithPlot;
    using ObjectEquationT =  ObjectDifferentialEquationRepresentation;
    using ObjectStateSpaceT =  ObjectStateSpaceRepresentation;
protected:
    PidTuningTest() : TestWithPlot(30.0) {}

    void
    test_closed_loop_control_object_differential_equation_representation()
    {
        Base::test_closed_loop_control(&_object_differential_equation_representation, &_pid_1, &_sine_wave1);
    }
    
    void
    test_tuner_object_differential_equation_representation()
    {
        Base::test_tuner<PidTuner>(_tuner_1);
    }

    void
    test_closed_loop_control_object_state_space_representation()
    {
        Base::test_closed_loop_control(&_object_state_space_representation, &_pid_2, &_sine_wave3);
    }
    
    void
    test_tuner_object_state_space_representation()
    {
        Base::test_tuner<PidTuner>(_tuner_2);
    }

private:
    SineWave _sine_wave1 {_time_step, 1.0, 1.0};
    SineWave _sine_wave2 {_time_step, 1.0, 1.0};
    PID _pid_1 {_time_step, {0.25, 1.0, 0.3}};
    ObjectEquationT _object_differential_equation_representation {_time_step, _order, {0.0, 0.0}, {2.0, 0.50, 3.0}};
    ControlSystem _system_1 {&_object_differential_equation_representation, &_pid_1, ControlMode::CLOSED_LOOP};
    PidTuner _tuner_1 {&_sine_wave2, _system_1, {}};

    SineWave _sine_wave3 {_time_step, 1.0, 1.0};
    SineWave _sine_wave4 {_time_step, 1.0, 1.0};
    PID _pid_2 {_time_step, {0.25, 1.0, 0.3}};
    ObjectStateSpaceT _object_state_space_representation {_time_step, _order, {0.0, 0.0}, {{{0.0, 1.0}, {-0.5, -2.0}}}, {0.0, 3.0}, {1.0, 0.0}};
    ControlSystem _system_2 {&_object_state_space_representation, &_pid_2, ControlMode::CLOSED_LOOP};
    PidTuner _tuner_2 {&_sine_wave4, _system_2, {}};
};

TEST_F(PidTuningTest, TunerWithObjectRepresentedByDifferentailEquationTest)
{
    // test_closed_loop_control_object_differential_equation_representation();
    test_tuner_object_differential_equation_representation();
}

TEST_F(PidTuningTest, TunerWithObjectRepresentedByStateSpaceTest)
{
    // test_closed_loop_control_object_state_space_representation();
    test_tuner_object_state_space_representation();
}