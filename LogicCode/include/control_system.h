// Author: Filip Dymczyk
// Description : Control loop system.

#pragma once
#include <memory>
#include "base_classes/controller_base.h"
#include "base_classes/object_representation_base.h"

// NOTE: Open/closed control system comprised of an object model and a controller.
class Control_System
{
public:
    enum class Control_Mode : std::uint8_t
    {
        OPEN_LOOP,
        CLOSED_LOOP,
        NONE
    };

    Control_System(
        Object_Representation_Base* object, std::shared_ptr<Controller_Base> controller,
        Control_Mode const& control_mode)
        : _object(object), _controller(std::move(controller)), _control_mode(control_mode)
    {
    }

    Control_System(Object_Representation_Base* object, Control_Mode const& control_mode)
        : Control_System(object, nullptr, control_mode)
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
            double error = set_point;
            if(_object != nullptr)
            {
                error -= _object->get_value();
            }

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

        if(_object != nullptr)
        {
            _object->update(object_update_value);
        }
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

    std::shared_ptr<Controller_Base> const
    get_controller() const
    {
        return _controller;
    }

    std::shared_ptr<Controller_Base>
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

    void
    set_controller(std::shared_ptr<Controller_Base> controller)
    {
        _controller = std::move(controller);
    }

private:
    Control_Mode _control_mode {};
    Object_Representation_Base* _object {nullptr};
    std::shared_ptr<Controller_Base> _controller {nullptr};
};