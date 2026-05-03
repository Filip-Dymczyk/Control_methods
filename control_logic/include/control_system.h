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
        CLOSED_LOOP,
        NONE
    };

    Control_System(Object_Representation_Base* object, Controller_Base* controller, Control_Mode const& control_mode)
        : m_object(object), m_controller(controller), m_control_mode(control_mode)
    {
    }

    Control_System(Object_Representation_Base* object, Control_Mode const& control_mode)
        : Control_System(object, nullptr, control_mode)
    {
    }

    void
    update(double set_point);

    double
    get_control() const;

    double
    get_output() const;

    double
    get_error() const;

    std::array<double, 3> const
    get_x() const;

    Controller_Base*
    get_controller() const;

    Control_Mode
    get_control_mode() const;

    void
    reset();

    void
    set_control_mode(Control_Mode control_mode);

    void
    set_controller(Controller_Base* controller);

    void
    set_object(Object_Representation_Base* object);

private:
    Object_Representation_Base* m_object {nullptr};
    Controller_Base* m_controller {nullptr};
    Control_Mode m_control_mode {};
};