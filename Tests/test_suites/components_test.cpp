// Author: Filip Dymczyk
// Description : Unit tests for individual components with sine wave signal as an input.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "signals.h"
#include "derivative.h"
#include "integrator.h"
#include "pid.h"
#include "object_differential_equation_representation.h"
#include "object_state_space_representation.h"

class ComponentsTest :  public testing::Test, public Test_With_Plot
{
    static constexpr std::uint32_t _order = 2u;
    static constexpr double _time_step = 0.01;
    std::vector<double> const init_state {0.0, 0.0};
protected:
    ComponentsTest() : Test_With_Plot(15.0) {}

    void
    test_integrator()
    {
        Test_With_Plot::test_component(&_integrator, &_sine_wave);
    }

    void
    test_derivative()
    {
        Test_With_Plot::test_component(&_derivative, &_sine_wave);
    }

    void
    test_pid()
    {
        Test_With_Plot::test_component(&_pid, &_sine_wave);
    }

    void
    test_object_differential_equation_representation()
    {
        Test_With_Plot::test_component(&_object_differential_equation, &_sine_wave);
    }

    void
    test_object_state_space_representation()
    {
        Test_With_Plot::test_component(&_object_state_space, &_sine_wave);
    }
private:
    Sine_Wave _sine_wave {_time_step, 1.0, 1.0, {}};
    Integrator _integrator {_time_step};
    Derivative _derivative {_time_step};
    PID _pid {_time_step, {1.0, 1.0, 1.0}};
    Object_Differential_Equation_Representation _object_differential_equation {_time_step, _order, init_state, {1.0, 1.0, 1.0}};
    Object_State_Space_Representation _object_state_space {_time_step, _order, init_state, {{{0.0, 1.0}, {-1.0, -1.0}}}, {0.0, 1.0}, {1.0, 0.0}};
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