// Author: Filip Dymczyk
// Description : Multi-order object representation base class.

#pragma once
#include <random>
#include <vector>
#include "simulation_object_base.h"
#include "state.h"

class Object_Representation_Base : public Simulation_Object_Base
{
public:
    struct State_Space_Matrices
    {
        std::vector<std::vector<double>> A {};
        std::vector<double> B {};
        std::vector<double> C {};
        double D {};
    };

    Object_Representation_Base(double time_step, std::size_t order, std::vector<double> const& init_state)
        : Simulation_Object_Base(time_step),
          _measurement_noise_on(false),
          _state(time_step, order, init_state),
          _order(order)
    {
    }

    void
    set_order(std::size_t order)
    {
        _order = order;
        _state.set_order(order);
    }

    std::size_t
    order() const
    {
        return _order;
    }

    void
    reset() override
    {
        set_value_with_measurement_noise(get_initial_output());
        _state.reset();
    }

    void
    set_time_step(double time_step)
    {
        _state.set_time_step(time_step);
    }

    virtual void
    set_parameters(std::vector<double> const&)
    {
    }

    virtual void
    set_parameters(State_Space_Matrices const&)
    {
    }

    void
    enable_measurement_noise(bool enable)
    {
        _measurement_noise_on = enable;
    }

    void
    set_measurement_noise_std(double measurement_noise_std)
    {
        std::normal_distribution<double>::param_type new_params(0.0, measurement_noise_std);
        _distribution.param(new_params);
    }

    void
    set_value_with_measurement_noise(double value)
    {
        double measurement_noise = 0.0;
        if(_measurement_noise_on)
        {
            measurement_noise = get_measurement_noise();
        }

        set_value(value + measurement_noise);
    }

protected:
    std::size_t _order {};
    State _state;

private:
    bool _measurement_noise_on;
    std::mt19937 _generator;
    std::normal_distribution<double> _distribution {0.0, 0.001};

    double
    get_measurement_noise()
    {
        return _distribution(_generator);
    }

    double
    get_initial_output() const
    {
        return _state.get_init_state(_order - 1);
    }
};