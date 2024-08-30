// Author: Filip Dymczyk
// Description : Control loop system.

#pragma once

enum class ControlMode
{
    OPEN_LOOP,
    CLOSED_LOOP
};

template<typename ObjectT, typename ControllerT>
class ControlSystem
{
public:
    ControlSystem(ObjectT const & object, ControllerT const & controller, ControlMode const & control_mode) : _object(object), _controller(controller), _control_mode(control_mode) {}

    void
    update(double const set_point)
    {
        _set_point = set_point;
        if(_control_mode == ControlMode::OPEN_LOOP)
        {
            _object.update(set_point);
        }
        else
        {
            double const error = set_point - _object.get_value();
            _controller.update(error);
            _object.update(_controller.get_value());
        }
    }

    double const
    get_set_point() const
    {
        return _set_point;
    }
    
    double const
    get_control() const
    {
        return _controller.get_value();
    }

    double const
    get_output() const
    {
        return _object.get_value();
    }
private:
    double _set_point {};
    ControlMode _control_mode {};
    ObjectT _object {};
    ControllerT _controller {};
};