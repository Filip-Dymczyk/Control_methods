// Author: Filip Dymczyk
// Description : Bang-Bang controller class.

#pragma once
#include "base_classes/controller_base.h"

// NOTE: Bang-Bang controller with hysteresis.
class Bang_Bang_Controller : public Controller_Base
{
    struct Bang_Bang_Controller_Parameters
    {
        double A1 {};
        double A2 {};
        double hist {};

        Bang_Bang_Controller_Parameters() = default;

        Bang_Bang_Controller_Parameters(std::vector<double> const& parameters)
        {
            assert(parameters.size() == 3u);

            A1   = parameters.at(0u);
            A2   = parameters.at(1u);
            hist = parameters.at(2u);
        }

        Bang_Bang_Controller_Parameters(std::initializer_list<double> const& parameters)
            : Bang_Bang_Controller_Parameters(std::vector<double>(parameters))
        {
        }
    };

public:
    Bang_Bang_Controller(double time_step, Bang_Bang_Controller_Parameters const& parameters)
        : Controller_Base(time_step), m_parameters(parameters)
    {
    }

    Bang_Bang_Controller(double time_step) : Bang_Bang_Controller(time_step, {}) {}

    void
    update(double error) override;

    void
    set_parameters(Bang_Bang_Controller_Parameters const& parameters)
    {
        m_parameters = parameters;
    }

    void
    set_parameters(std::vector<double> const& parameters) override
    {
        m_parameters = {parameters};
    }

    void
    reset() override;

private:
    Bang_Bang_Controller_Parameters m_parameters;
};