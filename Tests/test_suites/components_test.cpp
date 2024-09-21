// Author: Filip Dymczyk
// Description : Unit tests for individual components with sine wave signal as an input.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals/signals.h"
#include "sim_objects/derivative.h"
#include "sim_objects/integrator.h"
#include "sim_objects/pid.h"
#include "sim_objects/object_differential_equation_representation.h"
#include "sim_objects/object_state_space_representation.h"

class ComponentsTest :  public testing::Test, public TestWithPlot
{
    static constexpr std::uint32_t _order = 2u;
    static constexpr double _time_step = 0.01;
    static constexpr std::array<double, _order> init_state {0.0, 0.0};
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
    test_object_differential_equation_representation()
    {
        test_component<ObjectDifferentialEquationRepresentation<_order>>(object_differential_equation, &sine_wave);
    }

    void
    test_object_state_space_representation()
    {
        test_component<ObjectStateSpaceRepresentation<_order>>(object_state_space, &sine_wave);
    }
private:
    SineWave sine_wave {_time_step, 1.0, 1.0};
    Integrator integrator {_time_step};
    Derivative derivative {_time_step};
    PID pid {_time_step, {1.0, 1.0, 1.0}};
    ObjectDifferentialEquationRepresentation<_order> object_differential_equation {_time_step, {1.0, 1.0, 1.0}, init_state};
    ObjectStateSpaceRepresentation<_order> object_state_space {_time_step, init_state, {{{1.0, 1.0}, {1.0, 1.0}}}, {0.0, 1.0}, {1.0, 0.0}};
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

TEST_F(ComponentsTest, ObjectDifferentialEquationRepresentationTest)
{
    test_object_differential_equation_representation();
}

TEST_F(ComponentsTest, ObjectStateSpaceRepresentationTest)
{
    test_object_state_space_representation();
}