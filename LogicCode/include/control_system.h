// Author: Filip Dymczyk
// Description : Control loop system.

#pragma once
#include "base_classes/controller_base.h"
#include "base_classes/object_representation_base.h"

// NOTE: Open/closed control system comprised of an object model and a controller.
class Control_System
{
public:
    enum class Control_Mode : std::uint8_t
    {
        OPEN_LOOP,
        CLOSED_LOOP
    };

    Control_System(Object_Representation_Base* object, Controller_Base*& controller, Control_Mode const& control_mode)
        : _object(object), _controller(controller), _control_mode(control_mode)
    {
    }

    void
    update(double set_point)
    {
        double object_update_value = set_point;

        if(_control_mode == Control_Mode::OPEN_LOOP)
        {
            if(_controller != nullptr)
            {
                _controller->update(set_point);
                object_update_value = _controller->get_value();
            }
        }
        else
        {
            double const error = set_point - _object->get_value();

            if(_controller != nullptr)
            {
                _controller->update(error);
                object_update_value = _controller->get_value();
            }
            else
            {
                object_update_value = error;
            }
        }

        _object->update(object_update_value);
    }

    double
    get_control() const
    {
        if(_controller != nullptr)
        {
            return _controller->get_value();
        }
        return 0.0;
    }

    double
    get_output() const
    {
        if(_object != nullptr)
        {
            return _object->get_value();
        }
        return 0.0;
    }

    double
    get_error() const
    {
        if(_controller != nullptr)
        {
            return _controller->get_error();
        }
        return 0.0;
    }

    std::array<double, 3> const
    get_x() const
    {
        if(_controller != nullptr)
        {
            return _controller->get_x();
        }
        return {};
    }

    Controller_Base const*
    get_controller() const
    {
        return _controller;
    }

    Controller_Base*
    get_controller()
    {
        return _controller;
    }

    Control_Mode
    get_control_mode() const
    {
        return _control_mode;
    }

    void
    reset()
    {
        _object->reset();

        if(_controller != nullptr)
        {
            _controller->reset();
        }
    }

    void
    set_control_mode(Control_Mode control_mode)
    {
        _control_mode = control_mode;
    }

private:
    Control_Mode _control_mode {};
    Object_Representation_Base* _object {nullptr};
    Controller_Base*& _controller;
};