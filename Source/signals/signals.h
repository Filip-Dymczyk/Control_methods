// Author: Filip Dymczyk
// Description : Basic signals.

#pragma once

// NOTE: Base class for signals.
class Signal
{
public:
    Signal(double const start_time, double const scaler) : _start_time(start_time), _scaler(scaler) {}

    virtual void
    update(double const time) = 0;

    double const 
    get_value() const
    {
        return _value;
    }

    void
    set_start_time(double const start_time)
    {
        _start_time = start_time;
    }

    void
    set_scaler(double const scaler)
    {
        _scaler = scaler;
    }
protected:
    double _start_time {};
    double _scaler {};

    void
    set_value(double const value)
    {
        _value = value;
    }
private:
    double _value {};
};

// NOTE: Heaviside function - a * 1(t - t0).
class Heaviside : public Signal
{
public:
    Heaviside(double const start_time = 0.0, double const scaler = 1.0) : Signal(start_time, scaler) {}

    void
    update(double const time) override
    {
        set_value((time > _start_time) ? _scaler : 0.0);
    }
};

// NOTE: Ramp function - a * (t - t0).
class Ramp : public Heaviside
{
public:
    Ramp(double const start_time = 0.0, double const scaler = 1.0) : Heaviside(start_time, scaler) {}

    void
    update(double const time) override
    {
        Heaviside::update(time);
        set_value(time * get_value());
    }
};

// NOTE: Rectangle - a * (1(t - t0) - 1(t - t1)).
class Rectangle : public Signal
{
public:
    Rectangle(double const start_time, double const end_time, double const scaler = 1.0) : Signal(start_time, scaler)
    {
        assert(end_time > start_time);
        _end_time = end_time;
    }

    void
    update(double const time) override
    {
        set_value((time > _start_time && time < _end_time) ? _scaler : 0.0);
    }
private:
    double _end_time {};
};


// NOTE: Sine wave - {a * sin(w * t) + b; t > t0
//                   {0.0; t <= t0.
class SineWave : public Signal
{
public:
    SineWave(double const start_time, double const scaler, double const omega, double const offset) : Signal(start_time, scaler), _omega(omega), _offset(offset) {}

    void
    update(double const time) override
    {
        set_value((time > _start_time) ? (_scaler * sin(_omega * time) + _offset) : 0.0);
    }
private:
    double _omega {};
    double _offset {};
};