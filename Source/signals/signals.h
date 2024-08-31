// Author: Filip Dymczyk
// Description : Basic input signals.

#pragma once

class Heaviside
{
public:
    Heaviside(double const start_time = 0.0, double const coefficient = 1.0) :_start_time(start_time), _coefficient(coefficient) {}

    void
    set_start_time(double const start_time)
    {
        _start_time = (start_time > 0.0) ? start_time : 0.0;
    }

    void
    set_coefficient(double const coefficient)
    {
        _coefficient = coefficient;
    }

    void
    update(double const time)
    {
        _value = (time > _start_time) ? _coefficient : 0.0;
    }

    double const
    get_value() const
    {
        return _value;
    }

private:
    double _start_time {};
    double _coefficient {};
    double _value {};
};
