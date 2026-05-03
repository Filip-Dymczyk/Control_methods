// Author: Filip Dymczyk
// Description : PID controller class.

#pragma once
#include "base_classes/controller_base.h"
#include "derivative.h"
#include "integrator.h"

// NOTE: PID output will be computed as - kp * x + ki * int_x + kd * x'.
class PID : public Controller_Base
{
    struct PID_Parameters
    {
        double kp {};
        double ki {};
        double kd {};

        PID_Parameters() = default;

        PID_Parameters(std::vector<double> const& parameters)
        {
            assert(parameters.size() == 3u);

            kp = parameters.at(0u);
            ki = parameters.at(1u);
            kd = parameters.at(2u);
        }

        PID_Parameters(std::initializer_list<double> const& parameters)
            : PID_Parameters(std::vector<double>(parameters))
        {
        }
    };

public:
    PID(double time_step, PID_Parameters const& parameters) : Controller_Base(time_step), m_parameters(parameters) {}

    PID(double time_step) : PID(time_step, PID_Parameters {}) {}

    void
    update(double error) override;

    std::array<double, 3> const
    get_x() const override;

    std::array<double, 3>
    get_parameters() const;

    void
    set_parameters(std::vector<double> const& parameters) override;

    void
    reset() override;

    void
    set_time_step(double time_step);

    void
    enable_derivative_filtering(bool enable);

    void
    set_derivative_filtering_coefficient(double filtering_coefficient);

private:
    PID_Parameters m_parameters {};
    Integrator m_error_int {get_time_step()};
    Derivative m_error_der {get_time_step()};
};