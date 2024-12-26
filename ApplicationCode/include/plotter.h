// Author : Filip Dymczyk
// Description : Plotter class used for visualization.

#pragma once
#include <vector>
#include "matplotlibcpp/matplotlibcpp.h"
#include "control_system.h"

namespace plt = matplotlibcpp;

class Plotter
{
    struct Plotting_Buffers
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
    };

public:
    void
    update(double time, double set_point, double control, double output)
    {
        _plotting_buffers.time.push_back(time);
        _plotting_buffers.set_point.push_back(set_point);
        _plotting_buffers.control.push_back(control);
        _plotting_buffers.output.push_back(output);
    }

    void
    plot(ControlMode const& control_mode)
    {
        plt::figure();
        switch(control_mode) 
        {
            case ControlMode::CLOSED_LOOP:
            {
                plt::title("Closed loop control system response");
                break;
            }
            case ControlMode::OPEN_LOOP:
            {
                plt::title("Open loop control system response");
                break;
            }
            default:
            {
                plt::title("Component response");
                break;
            }
        } 

        plt::plot(_plotting_buffers.time, _plotting_buffers.set_point, "r-", {{"label", "set point"}});
        plt::plot(_plotting_buffers.time, _plotting_buffers.control, "y-", {{"label", "control"}});
        plt::plot(_plotting_buffers.time, _plotting_buffers.output, "b-", {{"label", "output"}});

        plt::xlabel("Time [s]");
        plt::ylabel("y");
        plt::legend("best");
        plt::grid();
        plt::show();   
    }
private:
    Plotting_Buffers _plotting_buffers {};
};