// Author: Filip Dymczyk
// Description : Class representing multi-order object state.

#pragma once
#include <vector>
#include "integrator.h"

class State
{
public:
    State(double time_step, std::size_t order, std::vector<double> const& initial_state);

    double
    get_value(std::size_t idx) const;

    double
    get_init_state(std::size_t idx) const;

    void
    update(double highest_order_derivative);

    void
    update(std::vector<double> const& new_state_derivative);

    void
    reset();

    void
    set_time_step(double time_step);

    void
    set_order(std::size_t order);

    void
    set_initial_conditions(std::vector<double> initial_conditions);

private:
    std::size_t m_order {};
    std::vector<double> m_initial_state {};
    std::vector<Integrator> m_integrators {};
};