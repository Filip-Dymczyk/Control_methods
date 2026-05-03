#include "pid_tuner.h"

Pid_Tuner::Pid_Tuner(Control_System& control_system, Recursive_Linear_Regression const& regression)
    : m_control_system(control_system), m_regression(regression)
{
}

void
Pid_Tuner::update(double input)
{
    assert(m_control_system.get_controller() != nullptr);

    m_control_system.update(input);
    m_regression.update(m_control_system.get_x(), m_control_system.get_error());
    m_control_system.get_controller()->set_parameters(
        {m_regression.get_coefficients()[0], m_regression.get_coefficients()[1], m_regression.get_coefficients()[2]});
}

double
Pid_Tuner::get_output() const
{
    return m_control_system.get_output();
}

double
Pid_Tuner::get_control() const
{
    return m_control_system.get_control();
}

void
Pid_Tuner::set_initial_pid_parameters(std::array<double, 3> pid_parameters)
{
    m_regression.set_initial_coefficients(pid_parameters);
}

void
Pid_Tuner::set_RLS_forgetting_factor(double forgetting_factor)
{
    m_regression.set_lambda(forgetting_factor);
}

void
Pid_Tuner::reset()
{
    m_control_system.reset();
    m_regression.reset();
}