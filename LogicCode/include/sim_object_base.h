// Author: Filip Dymczyk
// Description : Base simulation object.

#pragma once
#include <iostream>
#include <assert.h>

class SimumlationObjectBase
{
public:
    SimumlationObjectBase() : _time_step(0.0) {}
    SimumlationObjectBase(double time_step) : _time_step(time_step) 
    {
        assert(_time_step > 0.0);
    }
    
    virtual void
    update(double /*some input*/) = 0;

    double
    get_time_step() const
    {
        return _time_step;
    }

    double
    get_value() const
    {
        return _value;
    }

    virtual void
    reset() = 0;

protected:
    void
    set_value(double value)
    {
        _value = value;
    }
private:
    double _value {};
    double _time_step {};
};
