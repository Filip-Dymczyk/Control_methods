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
    static constexpr std::uint8_t order = 2u;
    static constexpr double _time_step = 0.01;
    using Base = TestWithPlot;
    
    using ObjectEquationT =  ObjectDifferentialEquationRepresentation<order>;
    using ControlSystemEquationT = ControlSystem<ObjectEquationT, PID>;
    using TunerEquationT = PidTuner<order, ObjectEquationT>;
    
    using ObjectStateSpaceT =  ObjectStateSpaceRepresentation<order>;
    using ControlSystemStateSpaceT = ControlSystem<ObjectStateSpaceT, PID>;
    using TunerStateSpaceT = PidTuner<order, ObjectStateSpaceT>;
protected:
    PidTuningTest() : TestWithPlot(30.0) {}

    void
    test_closed_loop_control_object_differential_equation_representation()
    {
        Base::test_closed_loop_control<ObjectEquationT, PID>(object_differential_equation_representation, pid_1, &sine_wave1);
    }
    
    void
    test_tuner_object_differential_equation_representation()
    {
        Base::test_tuner<TunerEquationT>(tuner_1);
    }

    void
    test_closed_loop_control_object_state_space_representation()
    {
        Base::test_closed_loop_control<ObjectStateSpaceT, PID>(object_state_space_representation, pid_2, &sine_wave3);
    }
    
    void
    test_tuner_object_state_space_representation()
    {
        Base::test_tuner<TunerStateSpaceT>(tuner_2);
    }

private:
    SineWave sine_wave1 {_time_step, 1.0, 1.0};
    SineWave sine_wave2 {_time_step, 1.0, 1.0};
    PID pid_1 {_time_step, {0.25, 1.0, 0.3}};
    ObjectEquationT object_differential_equation_representation {_time_step, {2.0, 0.50, 3.0}, {0.0, 0.0}};
    ControlSystemEquationT system_1 {object_differential_equation_representation, pid_1, ControlMode::CLOSED_LOOP};
    TunerEquationT tuner_1 {&sine_wave2, system_1, {}};

    SineWave sine_wave3 {_time_step, 1.0, 1.0};
    SineWave sine_wave4 {_time_step, 1.0, 1.0};
    PID pid_2 {_time_step, {0.25, 1.0, 0.3}};
    ObjectStateSpaceT object_state_space_representation {_time_step, {0.0, 0.0}, {{{0.0, 1.0}, {-0.5, -2.0}}}, {0.0, 3.0}, {1.0, 0.0}};
    ControlSystemStateSpaceT system_2 {object_state_space_representation, pid_2, ControlMode::CLOSED_LOOP};
    TunerStateSpaceT tuner_2 {&sine_wave4, system_2, {}};
};

TEST_F(PidTuningTest, TunerWithObjectRepresentedByDifferentailEquationTest)
{
    test_closed_loop_control_object_differential_equation_representation();
    test_tuner_object_differential_equation_representation();
}

TEST_F(PidTuningTest, TunerWithObjectRepresentedByStateSpaceTest)
{
    test_closed_loop_control_object_state_space_representation();
    test_tuner_object_state_space_representation();
}