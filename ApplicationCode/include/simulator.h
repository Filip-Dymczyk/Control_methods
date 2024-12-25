// Author : Filip Dymczyk
// Description : Simulator class connects Control class to Plotter class.

#pragma once

#include "input_parameters_container.h"
#include "control.h"
#include "plotter.h"

class Simulator
{
public:
    void
    update(InputParameterContainer const& input_parameters)
    {
        
    }

    void
    simulate()
    {

    }

    void
    show_plot()
    {
        _plotter.plot();
    }
private:
    Control _control;
    Plotter _plotter;
};