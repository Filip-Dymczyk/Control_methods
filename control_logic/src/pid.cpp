#include "pid.h"

void
PID::update(double error)
{
    set_error(error);
    m_error_int.update(error);
    m_error_der.update(error);
    set_value(
        m_parameters.kp * error + m_parameters.ki * m_error_int.get_value() +
        m_parameters.kd * m_error_der.get_value());
}

std::array<double, 3> const
PID::get_x() const
{
    return {get_error(), m_error_int.get_value(), m_error_der.get_value()};
}

std::array<double, 3>
PID::get_parameters() const
{
    return {m_parameters.kp, m_parameters.ki, m_parameters.kd};
}

void
PID::set_parameters(std::vector<double> const& parameters)
{
    m_parameters = parameters;
}

void
PID::reset()
{
    set_error(0.0);
    set_value(0.0);
    m_error_int.reset();
    m_error_der.reset();
}

void
PID::set_time_step(double time_step)
{
    Simulation_Object_Base::set_time_step(time_step);
    m_error_int.set_time_step(get_time_step());
    m_error_der.set_time_step(get_time_step());
}

void
PID::enable_derivative_filtering(bool enable)
{
    m_error_der.enable_filtering(enable);
}

void
PID::set_derivative_filtering_coefficient(double filtering_coefficient)
{
    m_error_der.set_filtering_coefficient(filtering_coefficient);
}