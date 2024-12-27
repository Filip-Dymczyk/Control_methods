// Author: Filip Dymczyk
// Description : Base class for regulators.

#pragma once
#include <array>
#include <vector>
#include "simulation_object_base.h"

struct PID_Params;

class Controller_Base : public Simulation_Object_Base
{
public:
    Controller_Base(double time_step) : Simulation_Object_Base(time_step) {}

    double
    get_error() const
    {
        return _error;
    }

    virtual std::array<double, 3> const 
    get_x() const 
    {
        return {};
    }

    virtual void
    set_parameters(std::vector<double> const&) = 0;

protected:
    void
    set_error(double error)
    {
        _error = error;
    }
private:
    double _error {};
};