// Author: Filip Dymczyk
// Description : Multi-order object representation base class.

#pragma once
#include <random>
#include <vector>
#include "sim_object_base.h"
#include "state.h"

class ObjectRepresentationBase : public SimumlationObjectBase
{   
public:
    ObjectRepresentationBase(double time_step, 
                            std::uint32_t order, 
                            std::vector<double> const & init_state) : 
                            SimumlationObjectBase(time_step), 
                            _state(time_step, order, init_state), 
                            _order(order)
    {}

    std::size_t
    order() const
    {
        return _order;
    }

    void
    reset() override
    {
        set_value(get_initial_output());
        _state.reset();
    }
protected:
    std::size_t _order {};
    State _state;

    double
    measurement_noise()
    {
        return distribution(generator);
    }
private:
    std::mt19937 generator;
    std::normal_distribution<double> distribution {0.0, 0.1};

    double
    get_initial_output() const
    {
        return _state.get_init_state(_order - 1);
    }
};