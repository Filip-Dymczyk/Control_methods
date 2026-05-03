#include "control_system.h"

void
Control_System::update(double set_point)
{
    double object_update_value = set_point;

    if(m_control_mode == Control_Mode::OPEN_LOOP)
    {
        if(m_controller != nullptr)
        {
            m_controller->update(set_point);
            object_update_value = m_controller->get_value();
        }
    }
    else
    {
        double error = set_point;
        if(m_object != nullptr)
        {
            error -= m_object->get_value();
        }

        if(m_controller != nullptr)
        {
            m_controller->update(error);
            object_update_value = m_controller->get_value();
        }
        else
        {
            object_update_value = error;
        }
    }

    if(m_object != nullptr)
    {
        m_object->update(object_update_value);
    }
}

double
Control_System::get_control() const
{
    if(m_controller != nullptr)
    {
        return m_controller->get_value();
    }
    return 0.0;
}

double
Control_System::get_output() const
{
    if(m_object != nullptr)
    {
        return m_object->get_value();
    }
    return 0.0;
}

double
Control_System::get_error() const
{
    if(m_controller != nullptr)
    {
        return m_controller->get_error();
    }
    return 0.0;
}

std::array<double, 3> const
Control_System::get_x() const
{
    if(m_controller != nullptr)
    {
        return m_controller->get_x();
    }
    return {};
}

Controller_Base*
Control_System::get_controller() const
{
    return m_controller;
}

Control_System::Control_Mode
Control_System::get_control_mode() const
{
    return m_control_mode;
}

void
Control_System::reset()
{
    if(m_object != nullptr)
    {
        m_object->reset();
    }

    if(m_controller != nullptr)
    {
        m_controller->reset();
    }
}

void
Control_System::set_control_mode(Control_System::Control_Mode control_mode)
{
    m_control_mode = control_mode;
}

void
Control_System::set_controller(Controller_Base* controller)
{
    m_controller = controller;
}

void
Control_System::set_object(Object_Representation_Base* object)
{
    m_object = object;
}