#include "bang_bang_controller.h"

void
Bang_Bang_Controller::update(double error)
{
    set_error(error);
    if(error >= (m_parameters.hist) / 2.0)
    {
        set_value(m_parameters.A2);
    }
    else if(error <= (-m_parameters.hist) / 2.0)
    {
        set_value(m_parameters.A1);
    }
}

void
Bang_Bang_Controller::reset()
{
    set_error(0.0);
    set_value(0.0);
}