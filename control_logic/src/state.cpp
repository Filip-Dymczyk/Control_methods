#include "state.h"

State::State(double time_step, std::size_t order, std::vector<double> const& initial_state)
{
    assert(order > 0u);
    assert(order == initial_state.size());

    m_order = order;
    m_initial_state.reserve(m_order);
    m_integrators.reserve(m_order);

    for(const auto& state: initial_state)
    {
        m_initial_state.push_back(state);
        m_integrators.emplace_back(time_step, state);
    }
}

double
State::get_value(std::size_t idx) const
{
    return m_integrators.at(idx).get_value();
}

double
State::get_init_state(std::size_t idx) const
{
    return m_initial_state.at(idx);
}

void
State::update(double highest_order_derivative)
{
    assert(m_order == m_integrators.size());

    // Next integrals of state derivatives:
    m_integrators.at(0).update(highest_order_derivative);
    for(std::size_t i = 1; i < m_order; i++)
    {
        m_integrators.at(i).update(m_integrators.at(i - 1).get_value());
    }
}

void
State::update(std::vector<double> const& new_state_derivative)
{
    assert(m_order == new_state_derivative.size());
    for(std::size_t i = 0; i < m_order; i++)
    {
        m_integrators.at(i).update(new_state_derivative.at(i));
    }
}

void
State::reset()
{
    assert(m_order == m_initial_state.size());
    assert(m_order == m_integrators.size());
    double const time_step = m_integrators.at(0).get_time_step();
    m_integrators.clear();

    for(std::size_t i = 0; i < m_order; i++)
    {
        m_integrators.emplace_back(time_step, m_initial_state.at(i));
    }
}

void
State::set_time_step(double time_step)
{
    for(auto& integrator: m_integrators)
    {
        integrator.set_time_step(time_step);
    }
}

void
State::set_order(std::size_t order)
{
    double const time_step = m_integrators.at(0).get_time_step();
    m_order                = order;
    m_initial_state        = std::vector<double>(order, 0.0);
    m_integrators.clear();
    m_integrators.reserve(m_order);

    for(double state: m_initial_state)
    {
        m_integrators.emplace_back(time_step, state);
    }
}

void
State::set_initial_conditions(std::vector<double> initial_conditions)
{
    assert(initial_conditions.size() == m_initial_state.size());
    m_initial_state = initial_conditions;
}