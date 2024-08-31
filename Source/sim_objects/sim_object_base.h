// Author: Filip Dymczyk
// Description : Base simulation object.

#pragma once
#include <iostream>

class SimumlationObjectBase
{
public:
    SimumlationObjectBase() : _time_step(0.0) {}
    SimumlationObjectBase(double const time_step) : _time_step(time_step) {}
    
    virtual void
    update(double const /*some input*/) = 0;

    double const
    get_time_step() const
    {
        return _time_step;
    }

    double const
    get_value() const
    {
        return _value;
    }

protected:
    void
    set_value(double const value)
    {
        _value = value;
    }
private:
    double _value {};
    double _time_step {};
};
