// Author: Filip Dymczyk
// Description : Two-position controller class.

#pragma once
#include "base_classes/controller_base.h"

struct Two_Position_Controller_Params
{
    double A1 {};
    double A2 {};
    double hist {};

    Two_Position_Controller_Params() = default;

    Two_Position_Controller_Params(double A1_in, double A2_in, double hist_in)
    {
        A1 = A1_in;
        A2 = A2_in;
        hist = hist_in;
    }

    Two_Position_Controller_Params(std::vector<double> const& parameters)
    {
        assert(parameters.size() == 3u);
        A1 = parameters.at(0u);
        A2 = parameters.at(1u);
        hist = parameters.at(2u);
    }
};
// TODO: Renaming for Bang_Bang_Controller
// NOTE: Two position controller with hysteresis.
class TwoPositionController : public ControllerBase
{
public:
    TwoPositionController(double time_step, Two_Position_Controller_Params const & params) : ControllerBase(time_step), _params(params) {}
    
    TwoPositionController(double time_step) : TwoPositionController(time_step, {}) {}
        
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
    set_parameters(Two_Position_Controller_Params const& parameters)
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
    }
private:
    Two_Position_Controller_Params _params {};
};