// Author: Filip Dymczyk
// Description : PID controller class.

#pragma once
#include "sim_object_base.h"
#include "integrator.h"
#include "derivative.h"


// NOTE: PID output will be computed as - kp * x + ki * int_x + kd * x'.
class PID : public SimumlationObjectBase
{
public:
    struct PID_Params
    {
        double kp {};
        double ki {};
        double kd {};
    };

    PID(double time_step, PID_Params const & params) : SimumlationObjectBase(time_step), _params(params) {}
    
    void
    update(double error) override
    {   
        _error = error;
        _error_int.update(error);
        _error_der.update(error);
        set_value(_params.kp * error + _params.ki * _error_int.get_value() + _params.kd * _error_der.get_value());
    }

    double
    get_error() const
    {
        return _error;
    }

    std::array<double, 3> const
    get_x() const 
    {
        return {_error, _error_int.get_value(), _error_der.get_value()};
    }

    void
    set_pid_params(PID_Params params)
    {
        _params = params;
    }
private:
    double _error {};
    PID_Params _params {};
    Integrator _error_int {get_time_step()};
    Derivative _error_der {get_time_step()};
};