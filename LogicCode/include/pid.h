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
};

// NOTE: PID output will be computed as - kp * x + ki * int_x + kd * x'.
class PID : public ControllerBase
{
public:
    PID(double time_step, PID_Params const & params) : ControllerBase(time_step), _params(params) {}
    
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
    set_params(PID_Params const & params) override
    {
        _params = params;
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