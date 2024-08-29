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

    PID(double const time_step, PID_Params params) : SimumlationObjectBase(time_step), _params(params) {}
    
    void
    update(double const input) override
    {   
        _error_int.update(input);
        _error_der.update(input);
        set_value(_params.kp * input + _params.ki * _error_int.get_value() + _params.kd * _error_der.get_value());
    }
private:  
    PID_Params _params {};
    Integrator _error_int {get_time_step()};
    Derivative _error_der {get_time_step()};
};