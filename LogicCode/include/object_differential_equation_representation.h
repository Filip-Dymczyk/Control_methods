// Author: Filip Dymczyk
// Description : Multi-order linear object represented by a single differential equation.

#pragma once
#include "base_classes/object_representation_base.h"

// NOTE: Object equation is taken as a highest order derivative which equals all the lower order ones multiplied by
// corresponding coefficients + input value. Lower order derivatives are equal to the integral of a higher one - simple
// relation. Object coefficients interpretation: e.g. x'' = -ax' - bx + cu. When entering coefficients beware of
// mistakenly creating unstable objects! We allow to set up desired initial conditions in a manner: {x'(0), x(0)}.
// Object already simulates measurement white noises (output).
class Object_Differential_Equation_Representation : public Object_Representation_Base
{
public:
    Object_Differential_Equation_Representation(
        double time_step, std::size_t order, std::vector<double> const& init_state,
        std::vector<double> const& coefficients)
        : Object_Representation_Base(time_step, order, init_state)
    {
        assert(coefficients.size() == order + 1u);
        _coefficients.reserve(order + 1u);
        _coefficients = coefficients;
    }

    Object_Differential_Equation_Representation(double time_step, std::size_t order)
        : Object_Differential_Equation_Representation(
              time_step, order, std::vector<double>(order), std::vector<double>(order + 1u))
    {
    }

    void
    update(double control) override
    {
        double highest_order_derivative_value = 0;

        // Calculating the highest derivative order:
        for(std::size_t i = 0; i < _coefficients.size(); i++)
        {
            if(i < _coefficients.size() - 1)
            {
                highest_order_derivative_value -= _coefficients.at(i) * _state.get_value(i);
            }
            else
            {
                highest_order_derivative_value += _coefficients.at(i) * control;
            }
        }
        // Update state variables values:
        _state.update(highest_order_derivative_value);

        // Output (x) - last integrator value;
        set_value_with_measurement_noise(_state.get_value(_order - 1));
    }

    void
    set_parameters(std::vector<double> const& object_parameters) override
    {
        assert(object_parameters.size() == (order() + 1u));
        _coefficients = object_parameters;
    }

    std::vector<double> const&
    get_coefficients() const
    {
        return _coefficients;
    }

private:
    std::vector<double> _coefficients {};
};