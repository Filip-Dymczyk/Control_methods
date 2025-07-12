// Author: Filip Dymczyk
// Description : Class representing multi-order object state.

#pragma once

#include <assert.h>
#include <cstdint>
#include <vector>
#include "integrator.h"

class State
{
public:
    State(double time_step, std::size_t order, std::vector<double> const& initial_state)
    {
        assert(order > 0u);
        assert(order == initial_state.size());

        _order = order;
        _initial_state.reserve(_order);
        _integrators.reserve(_order);

        for(const auto& state: initial_state)
        {
            _initial_state.push_back(state);
            Integrator I {time_step, state};
            _integrators.push_back(I);
        }
    }

    double
    get_value(std::size_t idx) const
    {
        assert(idx < _integrators.size());
        return _integrators.at(idx).get_value();
    }

    double
    get_init_state(std::size_t idx) const
    {
        assert(idx < _initial_state.size());
        return _initial_state.at(idx);
    }

    void
    update(double highest_order_derivative)
    {
        assert(_order == _integrators.size());
        // Next integrals of state derivatives:
        _integrators.at(0).update(highest_order_derivative);
        for(std::size_t i = 1; i < _order; i++)
        {
            _integrators.at(i).update(_integrators.at(i - 1).get_value());
        }
    }

    void
    update(std::vector<double> const& new_state_derivative)
    {
        assert(_order == new_state_derivative.size());
        for(std::size_t i = 0; i < _order; i++)
        {
            _integrators.at(i).update(new_state_derivative.at(i));
        }
    }

    void
    reset()
    {
        assert(_order == _initial_state.size());
        assert(_order == _integrators.size());
        double const time_step = _integrators.at(0).get_time_step();
        for(std::size_t i = 0; i < _order; i++)
        {
            Integrator I {time_step, _initial_state.at(i)};
            _integrators.at(i) = I;
        }
    }

    void
    set_time_step(double time_step)
    {
        for(auto& integrator: _integrators)
        {
            integrator.set_time_step(time_step);
        }
    }

    void
    set_order(std::size_t order)
    {
        double const time_step = _integrators.at(0).get_time_step();
        _order                 = order;
        _initial_state         = std::vector<double>(order, 0.0);
        _integrators           = {};
        _integrators.reserve(_order);

        for(const auto& state: _initial_state)
        {
            Integrator I {time_step, state};
            _integrators.push_back(I);
        }
    }

    void
    set_initial_conditions(std::vector<double> initial_conditions)
    {
        assert(initial_conditions.size() == _initial_state.size());
        _initial_state = initial_conditions;
    }

private:
    std::size_t _order {};
    std::vector<double> _initial_state {};
    std::vector<Integrator> _integrators {};
};