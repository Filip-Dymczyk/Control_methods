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
        std::vector<double> const& object_parameters, double control_signal_scaler);

    Object_Differential_Equation_Representation(double time_step, std::size_t order);

    void
    update(double control) override;

    void
    set_parameters(std::vector<double> const& object_parameters) override;

    void
    set_control_signal_scaler(double control_signal_scaler);

    std::vector<double> const&
    get_object_parameters() const;

private:
    std::vector<double> m_object_parameters {};
    double m_control_signal_scaler;
};