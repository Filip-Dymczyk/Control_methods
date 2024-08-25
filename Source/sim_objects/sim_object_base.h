// Author: Filip Dymczyk
// Description : Base simulation object.

#pragma once
#include <iostream>

class SimumlationObjectBase
{
public:
    SimumlationObjectBase() : _timelevel(0.0) {}
    SimumlationObjectBase(double const timelevel) : _timelevel(timelevel) {}
    
    virtual void
    update(double const input) = 0;

    double const
    get_timelevel() const
    {
        return _timelevel;
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
    double _timelevel {};
};
