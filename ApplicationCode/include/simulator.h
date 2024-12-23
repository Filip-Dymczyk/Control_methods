// Author : Filip Dymczyk
// Description : Simulator class connects Control class to Plotter class.

#pragma once

#include "control.h"
#include "plotter.h"

class Simulator
{
public:
    void
    show_plot()
    {
        _plotter.plot();
    }
private:
    Control _control;
    Plotter _plotter;
};