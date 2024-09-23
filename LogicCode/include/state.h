// Author: Filip Dymczyk
// Description : Class representing multi-order object state.

#pragma once

#include <cstdint>
#include <vector>
#include <assert.h>
#include "integrator.h"

class State
{
public:
    State(double time_step, std::uint32_t order, std::vector<double> const & init_state)
    {
        assert(order > 0u);
        assert(order == init_state.size());
        _order = order;
        for(const auto & state : init_state)
        {
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
    update(std::vector<double> const & new_state_derivative)
    {
        assert(_order == new_state_derivative.size());
        for(std::size_t i = 0; i < _order; i++)
        {
            _integrators.at(i).update(new_state_derivative.at(i));
        }
    }
private:
    std::uint32_t _order {};
    std::vector<Integrator> _integrators;
};