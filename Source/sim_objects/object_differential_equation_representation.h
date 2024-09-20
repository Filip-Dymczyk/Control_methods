// Author: Filip Dymczyk
// Description : Multi-order linear object represented by a single differential equation.

#pragma once
#include <random>
#include "sim_object_base.h"
#include "state.h"

// NOTE: Object equation is taken as a highest order derivative which equals all the lower order ones multiplied by corresponding coefficients + input value.
// Lower order derivatives are equal to the integral of a higher one - simple relation.
// Object coefficients interpretaion: e.g. x'' = -ax' - bx + cu.
// When entering coeficients beware of mistakingly creating unstable objects!
// We allow to set up desired initial conditions in a manner: {x'(0), x(0)}.
// Object already simulates measurement white noises (output).
template<std::size_t order>
class ObjectDifferentialEquationRepresentation : public SimumlationObjectBase
{   
public:
    using coeffs = std::array<double, order + 1>;
    using initial_state = std::array<double, order>;

    ObjectDifferentialEquationRepresentation(double time_step, coeffs const & coefficients, initial_state const & init_state) : SimumlationObjectBase(time_step), _coefficients(coefficients), _state(time_step, init_state)
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
    std::size_t const _order = order;
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