// Author: Filip Dymczyk
// Description : Multi-order linear objects.

#pragma once
#include <array>
#include "sim_object_base.h"
#include "integrator.h"
#include <assert.h>
#include <random>

// NOTE: Class representing state variables.
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
            Integrator I (time_step, init_state[i]);
            _integrators[i] = I;
        }
    }

    double
    get_value(std::size_t idx) const
    {
        return _integrators[idx].get_value();
    }

    void
    update(double input)
    {
        // Next integrals of state derivatives:
        _integrators[0].update(input);
        for(std::size_t i = 1; i < order; i++)
        {
            _integrators[i].update(_integrators[i - 1].get_value());
        }
    }
private:
    std::array<Integrator, order> _integrators;
};

// NOTE: Object equation is taken as a highest order derivative which equals all the lower order ones multiplied by corresponding coefficients + input value.
// Lower order derivatives are equal to the integral of a higher one - simple relation.
// Object coefficients interpretaion: e.g. x'' = -ax' - bx + cu.
// When entering coeficients beware of mistakingly creating unstable objects!
// We allow to set up desired initial conditions in a manner: {x'(0), x(0)}.
// Object already simulates measurement white noises (output).
template<std::size_t order>
class ObjectStandardRepresentation : public SimumlationObjectBase
{   
public:
    using coeffs = std::array<double, order + 1>;
    using initial_state = std::array<double, order>;

    ObjectStandardRepresentation(double time_step, coeffs const & coefficients, initial_state const & init_state) : SimumlationObjectBase(time_step), _coefficients(coefficients), _state(time_step, init_state)
    {}

    void 
    update(double control) override
    {
        double highest_order_derivative_value = 0;
        
        // Calculating the highest derivative order:
        for(std::size_t i = 0; i < _coefficients.size(); i++)
        {
            if(i < _coefficients.size() - 1)
            {
                highest_order_derivative_value -= _coefficients[i] * _state.get_value(i);
            }
            else
            {
                highest_order_derivative_value += _coefficients[i] * control;
            }
        }
        // Update state variables values:
        _state.update(highest_order_derivative_value);

        // Output (x) - last integrator value;
        set_value(_state.get_value(_order - 1) + measurement_noise());
    }

    std::size_t
    get_order() const
    {
        return _order;
    }
    
    coeffs const &
    get_coefss() const
    {
        return _coefficients;
    }
private:
    std::size_t _order = order;
    coeffs _coefficients;
    State<order> _state;

    std::mt19937 generator;
    std::normal_distribution<double> distribution {0.0, 0.1};

    double
    measurement_noise()
    {
        return distribution(generator);
    }
};