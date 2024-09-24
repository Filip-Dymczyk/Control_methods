// Author: Filip Dymczyk
// Description : Base class for regulators.

#pragma once
#include <array>
#include "sim_object_base.h"

struct PID_Params;

class ControllerBase : public SimumlationObjectBase
{
public:
    ControllerBase(double time_step) : SimumlationObjectBase(time_step) {}

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
    set_params(PID_Params const &) 
    {
        
    }

protected:
    void
    set_error(double error)
    {
        _error = error;
    }
private:
    double _error {};
};