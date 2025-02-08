// Author: Filip Dymczyk
// Description : PID controller class.

#pragma once
#include "base_classes/controller_base.h"
#include "derivative.h"
#include "integrator.h"

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

    PID_Parameters(std::initializer_list<double> const& parameters) : PID_Parameters(std::vector<double>(parameters)) {}
};

// NOTE: PID output will be computed as - kp * x + ki * int_x + kd * x'.
class PID : public Controller_Base
{
public:
    PID(double time_step, PID_Parameters const& parameters) : Controller_Base(time_step), _parameters(parameters) {}

    PID(double time_step) : PID(time_step, {}) {}

    void
    update(double error) override
    {
        set_error(error);
        _error_int.update(error);
        _error_der.update(error);
        set_value(
            _parameters.kp * error + _parameters.ki * _error_int.get_value() + _parameters.kd * _error_der.get_value());
    }

    std::array<double, 3> const
    get_x() const override
    {
        return {get_error(), _error_int.get_value(), _error_der.get_value()};
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
        _error_int.reset();
        _error_der.reset();
    }

    void
    set_time_step(double time_step)
    {
        Simulation_Object_Base::set_time_step(time_step);
        _error_int.set_time_step(get_time_step());
        _error_der.set_time_step(get_time_step());
    }

private:
    PID_Parameters _parameters {};
    Integrator _error_int {get_time_step()};
    Derivative _error_der {get_time_step()};
};