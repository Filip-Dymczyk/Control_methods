// Author: Filip Dymczyk
// Description : Base class for regulators.

#pragma once
#include "sim_object_base.h"

template<typename Params>
class RegulatorBase : public SimumlationObjectBase
{
public:
    RegulatorBase(double time_step, Params const & params) : SimumlationObjectBase(time_step), _params(params) {}

    double
    get_error() const
    {
        return _error;
    }

    void
    set_params(Params const & params)
    {
        _params = params;
    }
protected:
    void
    set_error(double error)
    {
        _error = error;
    }

    Params const & 
    get_params() const
    {
        return _params;
    }
private:
    double _error {};
    Params _params {};
};