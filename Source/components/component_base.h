// Author: Filip Dymczyk
// Description : Base class for components.

#pragma once
#include <iostream>

class ComponentBase
{
public:
    ComponentBase(double timelevel) : _timelevel(timelevel) {}
    
    virtual void
    update(double input) = 0;

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
    set_value(double value)
    {
        _value = value;
    }
private:
    double _value {};
    double _timelevel {};
};
