// Author: Filip Dymczyk
// Description : Two-position controller class.

#pragma once
#include "controller_base.h"

struct Two_Position_Controller_Params
{
    double A1 {};
    double A2 {1.0};
    double hist {};
};

// NOTE: Two position controller with histeresis.
class TwoPositionController : public ControllerBase
{
public:
    TwoPositionController(double time_step, Two_Position_Controller_Params const & params = {}) : ControllerBase(time_step), _params(params) {}
    
    void
    update(double error) override
    {   
        set_error(error);
        if(error >= (_params.hist) / 2.0)
        {
            set_value(_params.A2);
        }
        else if(error <= (-_params.hist) / 2.0)
        {
            set_value(_params.A1);
        }
    }

    void
    set_params(Two_Position_Controller_Params const & params)
    {
        _params = params;
    }

    void 
    reset() override
    {
        set_error(0.0);
        set_value(0.0);
    }
private:
    Two_Position_Controller_Params _params {};
};