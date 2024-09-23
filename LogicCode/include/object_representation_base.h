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
    ObjectRepresentationBase(double time_step, std::uint32_t order, std::vector<double> const & init_state) : SimumlationObjectBase(time_step), _state(time_step, order, init_state), _order(order)
    {}

    std::size_t
    order() const
    {
        return _order;
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
};