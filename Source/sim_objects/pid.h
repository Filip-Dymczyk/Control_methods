// Author: Filip Dymczyk
// Description : PID controller class.

#pragma once
#include "regulator_base.h"
#include "integrator.h"
#include "derivative.h"

struct PID_Params
{
    double kp {};
    double ki {};
    double kd {};
};

// NOTE: PID output will be computed as - kp * x + ki * int_x + kd * x'.
class PID : public RegulatorBase<PID_Params>
{
public:
    PID(double time_step, PID_Params const & params) : RegulatorBase(time_step, params) {}
    
    void
    update(double error) override
    {   
        set_error(error);
        _error_int.update(error);
        _error_der.update(error);
        set_value(get_params().kp * error + get_params().ki * _error_int.get_value() + get_params().kd * _error_der.get_value());
    }

    std::array<double, 3> const
    get_x() const 
    {
        return {get_error(), _error_int.get_value(), _error_der.get_value()};
    }
private:
    Integrator _error_int {get_time_step()};
    Derivative _error_der {get_time_step()};
};