// Author: Filip Dymczyk
// Description : PID controller class.

#pragma once
#include "base_classes/controller_base.h"
#include "integrator.h"
#include "derivative.h"

struct PID_Params
{
    double kp {};
    double ki {};
    double kd {};

    PID_Params() = default;

    PID_Params(double kp_in, double ki_in, double kd_in)
    {
        kp = kp_in;
        ki = ki_in;
        kd = kd_in;
    }

    PID_Params(std::vector<double> const& parameters)
    {
        assert(parameters.size() == 3u);

        kp = parameters.at(0u);
        ki = parameters.at(1u);
        kd = parameters.at(2u);
    }
};

// NOTE: PID output will be computed as - kp * x + ki * int_x + kd * x'.
class PID : public ControllerBase
{
public:
    PID(double time_step, PID_Params const & params) : ControllerBase(time_step), _params(params) {}

    PID(double time_step) : PID(time_step, {}) {}
    
    void
    update(double error) override
    {   
        set_error(error);
        _error_int.update(error);
        _error_der.update(error);
        set_value(_params.kp * error + _params.ki * _error_int.get_value() + _params.kd * _error_der.get_value());
    }

    std::array<double, 3> const
    get_x() const override
    {
        return {get_error(), _error_int.get_value(), _error_der.get_value()};
    }

    void
    set_parameters(PID_Params const& parameters) override
    {
        _params = parameters;
    }

    void
    set_parameters(std::vector<double> const& parameters)
    {
        _params = {parameters};
    }

    void
    reset() override
    {
        set_error(0.0);
        set_value(0.0);
        _error_int.reset();
        _error_der.reset();
    }
private:
    PID_Params _params {};
    Integrator _error_int {get_time_step()};
    Derivative _error_der {get_time_step()};
};