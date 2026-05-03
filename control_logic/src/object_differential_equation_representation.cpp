#include "object_differential_equation_representation.h"

Object_Differential_Equation_Representation::Object_Differential_Equation_Representation(
    double time_step, std::size_t order, std::vector<double> const& init_state,
    std::vector<double> const& object_parameters, double control_signal_scaler)
    : Object_Representation_Base(time_step, order, init_state)
{
    assert(object_parameters.size() == order);
    m_object_parameters.reserve(order);
    m_object_parameters     = object_parameters;
    m_control_signal_scaler = control_signal_scaler;
}

Object_Differential_Equation_Representation::Object_Differential_Equation_Representation(
    double time_step, std::size_t order)
    : Object_Differential_Equation_Representation(
          time_step, order, std::vector<double>(order), std::vector<double>(order), 0.0)
{
}

void
Object_Differential_Equation_Representation::update(double control)
{
    double highest_order_derivative_value = 0.0;
    for(std::size_t i = 0; i < m_object_parameters.size(); i++)
    {
        highest_order_derivative_value -= m_object_parameters.at(i) * m_state.get_value(i);
    }
    highest_order_derivative_value += m_control_signal_scaler * control;

    // Update state variables values:
    m_state.update(highest_order_derivative_value);

    // Output (x) - last integrator value;
    set_value_with_measurement_noise(m_state.get_value(m_order - 1));
}

void
Object_Differential_Equation_Representation::set_parameters(std::vector<double> const& object_parameters)
{
    assert(object_parameters.size() == order());
    m_object_parameters = object_parameters;
}

void
Object_Differential_Equation_Representation::set_control_signal_scaler(double control_signal_scaler)
{
    m_control_signal_scaler = control_signal_scaler;
}

std::vector<double> const&
Object_Differential_Equation_Representation::get_object_parameters() const
{
    return m_object_parameters;
}