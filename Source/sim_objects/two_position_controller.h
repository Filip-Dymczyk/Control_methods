// Author: Filip Dymczyk
// Description : Two-position controller class.

#pragma once
#include "regulator_base.h"
#include "integrator.h"
#include "derivative.h"

struct Two_Position_Controller_Params
{
    double A1 {};
    double A2 {1.0};
    double hist {};
};

// NOTE: Two position controller with histeresis.
class TwoPositionController : public RegulatorBase<Two_Position_Controller_Params>
{
public:
    TwoPositionController(double time_step, Two_Position_Controller_Params const & params = {}) : RegulatorBase(time_step, params) {}
    
    void
    update(double error) override
    {   
        set_error(error);
        if(error >= (get_params().hist) / 2.0)
        {
            set_value(get_params().A2);
        }
        else if(error <= (-get_params().hist) / 2.0)
        {
            set_value(get_params().A1);
        }
    }
};