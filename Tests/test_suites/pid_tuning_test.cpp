// Author: Filip Dymczyk
// Description : Unit tests for pid tuning operation.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals/signals.h"
#include "sim_objects/pid.h"
#include "sim_objects/object.h"
#include "sim_objects/control_system.h"
#include "regression/recursive_linear_regression.h"
#include "pid_tuner/pid_tuner.h"

static constexpr uint8_t order = 2u;
class PidTuningTest :  public testing::Test, public TestWithPlot
{   
    using Base = TestWithPlot;
    using ObjectT =  ObjectStandardRepresentation<order>;
    using ControlSystemT = ControlSystem<ObjectT, PID>;
    using TunerT = PidTuner<order>;
protected:
    PidTuningTest() : TestWithPlot(30.0) {}

    void
    test_tuner()
    {
        Base::test_tuner<TunerT>(tuner);
    }

    void
    test_closed_loop_control()
    {
        Base::test_closed_loop_control<ObjectT, PID>(object, pid, &sine_wave1);
    }

private:
    double const _time_step = 0.01;
    SineWave sine_wave1 {_time_step, 1.0, 1.0};
    SineWave sine_wave2 {_time_step, 1.0, 1.0};
    PID pid {_time_step, {0.25, 1.0, 0.3}};
    ObjectT object {_time_step, {2.0, 0.50, 3.0}, {0.0, 0.0}};
    ControlSystemT system {object, pid, ControlMode::CLOSED_LOOP};
    TunerT tuner {&sine_wave2, system, {}};
};

TEST_F(PidTuningTest, TunerTest)
{
    test_closed_loop_control();
    test_tuner();
}