// Author: Filip Dymczyk
// Description : Class representing multi-order object state.

#pragma once

#include <cstdint>
#include <array>
#include <assert.h>
#include "integrator.h"

template<std::size_t order>
class State
{
public:
    using initial_state = std::array<double, order>;

    State(double time_step, initial_state const & init_state)
    {
        assert(order > 0u);

        for(std::size_t i = 0; i < order; i++)
        {
            Integrator I {time_step, init_state[i]};
            _integrators[i] = I;
        }
    }

    double
    get_value(std::size_t idx) const
    {
        return _integrators[idx].get_value();
    }

    void
    update(double highest_order_deriavtive)
    {
        // Next integrals of state derivatives:
        _integrators[0].update(highest_order_deriavtive);
        for(std::size_t i = 1; i < order; i++)
        {
            _integrators[i].update(_integrators[i - 1].get_value());
        }
    }

    void
    update(std::array<double, order> const & new_state_derivative)
    {
        for(std::size_t i = 0; i < order; i++)
        {
            _integrators[i].update(new_state_derivative[i]);
        }
    }
private:
    std::array<Integrator, order> _integrators;
};