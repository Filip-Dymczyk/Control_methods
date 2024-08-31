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

    virtual void
    update(double const time)
    {
        _value = (time > _start_time) ? _coefficient : 0.0;
    }

    double const
    get_value() const
    {
        return _value;
    }

protected:
    double _start_time {};
    double _coefficient {};

    void
    set_value(double const value)
    {
        _value = value;
    }
private:
    double _value {};
};

class Ramp : public Heaviside
{
public:
    Ramp(double const start_time = 0.0, double const coefficient = 1.0) : Heaviside(start_time, coefficient) {}

    void
    update(double const time) override
    {
        set_value((time > _start_time) ? _coefficient * time : 0.0);
    }
};

