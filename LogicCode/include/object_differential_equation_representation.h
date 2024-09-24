// Author: Filip Dymczyk
// Description : Multi-order linear object represented by a single differential equation.

#pragma once
#include "object_representation_base.h"

// NOTE: Object equation is taken as a highest order derivative which equals all the lower order ones multiplied by corresponding coefficients + input value.
// Lower order derivatives are equal to the integral of a higher one - simple relation.
// Object coefficients interpretaion: e.g. x'' = -ax' - bx + cu.
// When entering coeficients beware of mistakingly creating unstable objects!
// We allow to set up desired initial conditions in a manner: {x'(0), x(0)}.
// Object already simulates measurement white noises (output).
class ObjectDifferentialEquationRepresentation : public ObjectRepresentationBase
{   
public:
    ObjectDifferentialEquationRepresentation(double time_step, std::uint32_t order,  
                                            std::vector<double> const & init_state, 
                                            std::vector<double> const & coefficients) : 
                                            ObjectRepresentationBase(time_step, order, init_state)
    {
        assert(coefficients.size() == order + 1);
        _coefficients = coefficients;
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
        set_value(_state.get_value(_order - 1) + measurement_noise());
    }
    
    std::vector<double> const &
    get_coefss() const
    {
        return _coefficients;
    }
private:
    std::vector<double> _coefficients {};
};