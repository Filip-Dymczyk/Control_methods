// Author: Filip Dymczyk
// Description : Unit tests for setting object initial conditions after creation.

#include <gtest/gtest.h>
#include "test_with_plot.h"
#include "object_differential_equation_representation.h"
#include "object_state_space_representation.h"
#include "signals.h"


class InitialConditionsSettingTest : public testing::Test, public Test_With_Plot
{
    static constexpr std::uint32_t _order = 2u;
    static constexpr double _time_step    = 0.01;

protected:
    InitialConditionsSettingTest() : Test_With_Plot(5.0) {}

    void
    test_object_differential_equation_representation()
    {
        _object_differential_equation.reset();
        Test_With_Plot::test_component(&_object_differential_equation, &_heaviside);
    }

    void
    test_object_state_space_representation()
    {
        _object_state_space.reset();
        Test_With_Plot::test_component(&_object_state_space, &_heaviside);
    }

    std::vector<std::vector<double>> const init_states = {{1.0, 0.0}, {3.0, 0.0}, {5.0, 1.0}};
    Heaviside _heaviside {_time_step, {0.0, 0.0}}; // Scaler set to 0 - response to initial conditions.
    Object_Differential_Equation_Representation _object_differential_equation {
        _time_step, _order, init_states.at(0), {1.0, 1.0, 1.0}};
    Object_State_Space_Representation _object_state_space {
        _time_step, _order, init_states.at(0), {{{0.0, 1.0}, {-1.0, -1.0}}}, {0.0, 1.0}, {1.0, 0.0}};
};

TEST_F(InitialConditionsSettingTest, ObjectDifferentialEquationRepresentationTest)
{
    test_object_differential_equation_representation();

    _object_differential_equation.set_initial_conditions(init_states.at(1));

    test_object_differential_equation_representation();

    _object_differential_equation.set_initial_conditions(init_states.at(2));

    test_object_differential_equation_representation();
}

TEST_F(InitialConditionsSettingTest, ObjectStateSpaceRepresentationTest) 
{ 
    test_object_state_space_representation();

    _object_state_space.set_initial_conditions(init_states.at(1));

    test_object_state_space_representation();

    _object_state_space.set_initial_conditions(init_states.at(2));

    test_object_state_space_representation();
}