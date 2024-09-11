// Author: Filip Dymczyk
// Description : Unit tests for individual components with sine wave signal as an input.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals/signals.h"
#include "sim_objects/derivative.h"
#include "sim_objects/integrator.h"
#include "sim_objects/pid.h"
#include "sim_objects/object.h"

class ComponentsTest :  public testing::Test, public TestWithPlot
{
protected:
    ComponentsTest() : TestWithPlot(15.0) {}

    void
    test_integrator()
    {
        test_component<Integrator>(integrator, &sine_wave);
    }

    void
    test_derivative()
    {
        test_component<Derivative>(derivative, &sine_wave);
    }

    void
    test_pid()
    {
        test_component<PID>(pid, &sine_wave);
    }

    void
    test_object()
    {
        test_component<ObjectStandardRepresentation<2>>(object, &sine_wave);
    }
private:
    double const _time_step = 0.01;
    SineWave sine_wave {_time_step, 1.0, 1.0};
    Integrator integrator {_time_step};
    Derivative derivative {_time_step};
    PID pid {_time_step, {1.0, 1.0, 1.0}};
    ObjectStandardRepresentation<2> object {_time_step, {1.0, 1.0, 1.0}, {0.0, 0.0}};
};

TEST_F(ComponentsTest, IntegratorTest)
{
    test_integrator();
}

TEST_F(ComponentsTest, DerivativeTest)
{
    test_derivative();
}

TEST_F(ComponentsTest, PidTest)
{
    test_pid();
}

TEST_F(ComponentsTest, ObjectTest)
{
    test_object();
}