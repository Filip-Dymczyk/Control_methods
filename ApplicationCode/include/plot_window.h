// Author : Filip Dymczyk 
// Description : Plot window layout.

#pragma once

#include <QtWidgets/QWidget>
#include "simulator.h"
#include "plotter.h"
#include <iostream>

class PlotWindow : public QWidget
{
public:
    void
    show_plot()
    {
        _plotter.plot();
    }

private:
    Simulator _simulator {};
    Plotter _plotter {1.0};
};
