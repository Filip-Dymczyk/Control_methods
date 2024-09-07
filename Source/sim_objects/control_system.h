// Author: Filip Dymczyk
// Description : Control loop system.

#pragma once

enum class ControlMode
{
    OPEN_LOOP,
    CLOSED_LOOP,
    NONE
};

// NOTE: Open/closed control system comprised of an object model and a controller.
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
            _controller.update(set_point);
        }
        else
        {
            double const error = set_point - _object.get_value();
            _controller.update(error);
        }
        _object.update(_controller.get_value());
    }

    double
    get_set_point() const
    {
        return _set_point;
    }
    
    double
    get_control() const
    {
        return _controller.get_value();
    }

    double
    get_output() const
    {
        return _object.get_value();
    }

    double
    get_error() const
    {
        return _controller.get_error();
    }

    std::array<double, 3> const 
    get_x() const 
    {
        return _controller.get_x();
    }
    
    void
    set_pid_params(std::array<double, 3> params)
    {
        _controller.set_pid_params({params.at(0), params.at(1), params.at(2)});
    }
private:
    double _set_point {};
    ControlMode _control_mode {};
    ObjectT _object {};
    ControllerT _controller {};
};