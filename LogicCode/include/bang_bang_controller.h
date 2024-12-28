// Author: Filip Dymczyk
// Description : Bang-Bang controller class.

#pragma once
#include "base_classes/controller_base.h"

struct Bang_Bang_Controller_Parameters
{
    double A1 {};
    double A2 {};
    double hist {};

    Bang_Bang_Controller_Parameters() = default;

    Bang_Bang_Controller_Parameters(std::vector<double> const& parameters)
    {
        assert(parameters.size() == 3u);

        A1 = parameters.at(0u);
        A2 = parameters.at(1u);
        hist = parameters.at(2u);
    }

    Bang_Bang_Controller_Parameters(std::initializer_list<double> const& parameters) : Bang_Bang_Controller_Parameters(std::vector<double>(parameters)) {}
};

// NOTE: Bang-Bang controller with hysteresis.
class Bang_Bang_Controller : public Controller_Base
{
public:
    Bang_Bang_Controller(double time_step, Bang_Bang_Controller_Parameters const & parameters) : Controller_Base(time_step), _parameters(parameters) {}
    
    Bang_Bang_Controller(double time_step) : Bang_Bang_Controller(time_step, {}) {}
        
    void
    update(double error) override
    {   
        set_error(error);
        if(error >= (_parameters.hist) / 2.0)
        {
            set_value(_parameters.A2);
        }
        else if(error <= (-_parameters.hist) / 2.0)
        {
            set_value(_parameters.A1);
        }
    }

    void
    set_parameters(Bang_Bang_Controller_Parameters const& parameters)
    {
        _parameters = parameters;
    }

    void
    set_parameters(std::vector<double> const& parameters) override
    {
        _parameters = {parameters};
    }

    void 
    reset() override
    {
        set_error(0.0);
        set_value(0.0);
    }
private:
    Bang_Bang_Controller_Parameters _parameters {};
};