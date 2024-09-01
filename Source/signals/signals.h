// Author: Filip Dymczyk
// Description : Basic signals.

#pragma once

// NOTE: Base class for signals.
class Signal
{
public:
    Signal(double start_time, double scaler) : _start_time(start_time), _scaler(scaler) {}

    virtual void
    update(double time) = 0;

    double 
    get_value() const
    {
        return _value;
    }

    void
    set_start_time(double start_time)
    {
        _start_time = start_time;
    }

    void
    set_scaler(double scaler)
    {
        _scaler = scaler;
    }

    void
    reset()
    {
        _value = 0.0;
    }
protected:
    double _start_time {};
    double _scaler {};

    void
    set_value(double value)
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
    Heaviside(double start_time = 0.0, double scaler = 1.0) : Signal(start_time, scaler) {}

    void
    update(double time) override
    {
        set_value((time > _start_time) ? _scaler : 0.0);
    }
};

// NOTE: Ramp function - a * (t - t0).
class Ramp : public Heaviside
{
public:
    Ramp(double start_time = 0.0, double scaler = 1.0) : Heaviside(start_time, scaler) {}

    void
    update(double time) override
    {
        Heaviside::update(time);
        set_value(time * get_value());
    }
};

// NOTE: Rectangle - a * (1(t - t0) - 1(t - t1)).
class Rectangle : public Signal
{
public:
    Rectangle(double start_time, double end_time, double scaler = 1.0) : Signal(start_time, scaler)
    {
        assert(end_time > start_time);
        _end_time = end_time;
    }

    void
    update(double time) override
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
    SineWave(double start_time, double scaler, double omega, double offset) : Signal(start_time, scaler), _omega(omega), _offset(offset) {}

    void
    update(double time) override
    {
        set_value((time > _start_time) ? (_scaler * sin(_omega * time) + _offset) : 0.0);
    }
private:
    double _omega {};
    double _offset {};
};