// Author: Filip Dymczyk
// Description : Tests with plots.

#pragma once
#include <math.h>
#include "matplotlibcpp/matplotlibcpp.h"
#include "sim_objects/pid.h"
#include "sim_objects/object.h"
#include "sim_objects/control_system.h"
#include "signals/signals.h"

namespace plt = matplotlibcpp;

// NOTE: Allows to components and control systems by plotting: set point, output and optionally - control value.
class TestWithPlot
{
    struct PlottingBuffers
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
    };

public:
    TestWithPlot(double sim_time, double time_step) : _sim_time(sim_time), _time_step(time_step) {}

    template<typename ObjectT>
    void
    test_closed_loop_control(ObjectT object, PID pid, Signal* input_signal, bool const plot_control = false)
    {
        PlottingBuffers const buffers = simulate_open_closed_loop(object, pid, input_signal, ControlMode::CLOSED_LOOP);

        plot_test(buffers.time, buffers.set_point, buffers.control, buffers.output, ControlMode::CLOSED_LOOP, plot_control);
    }

    template<typename ObjectT>
    void
    test_open_loop_control(ObjectT object, PID pid, Signal* input_signal, bool const plot_control = false)
    {
        PlottingBuffers const buffers = simulate_open_closed_loop(object, pid, input_signal, ControlMode::OPEN_LOOP);

        plot_test(buffers.time, buffers.set_point, buffers.control, buffers.output, ControlMode::OPEN_LOOP, plot_control);
    }

    template<typename ComponentT>
    void
    test_component(ComponentT component, Signal* input_signal)
    {
        PlottingBuffers const buffers = simulate_component(component, input_signal);

        plot_test(buffers.time, buffers.set_point, buffers.control, buffers.output, ControlMode::NONE, false);
    }

    void
    set_sim_time(double sim_time)
    {
        _sim_time = sim_time;
    }

    void
    set_time_step(double time_step)
    {
        _time_step = time_step;
    }

private:
    double _sim_time {};
    double _time_step {};

    template<typename ObjectT>
    PlottingBuffers const
    simulate_open_closed_loop(ObjectT object, PID pid, Signal* input_signal, ControlMode const & control_mode)
    {
        input_signal -> reset();
        ControlSystem<ObjectT, PID> control_loop {object, pid, control_mode};
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
        
        double t = 0;
        while(t < _sim_time)
        {
            time.push_back(t);
            control_loop.update(input_signal -> get_value());
            set_point.push_back(input_signal -> get_value());
            control.push_back(control_loop.get_control());
            output.push_back(control_loop.get_output());
            t += _time_step;
            input_signal -> update(t);
        }  
        return {time, set_point, control, output};
    }

    template<typename ComponentT>
    PlottingBuffers const
    simulate_component(ComponentT object, Signal* input_signal)
    {
        input_signal -> reset();
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> output {};

        double t = 0;
        while(t < _sim_time)
        {
            time.push_back(t);
            object.update(input_signal -> get_value());   
            set_point.push_back(input_signal -> get_value());
            output.push_back(object.get_value());
            t += _time_step;
            input_signal -> update(t);
        }  
        return {time, set_point, {}, output};
    }

    void
    plot_test(std::vector<double> const & time, std::vector<double> const & set_point, std::vector<double> const & control, std::vector<double> const & output, ControlMode const & control_mode, bool plot_control)
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
        
        plt::plot(time, set_point, "r-", {{"label", "set point"}});
        if(plot_control)
        {
            plt::plot(time, control, "y-", {{"label", "control"}});
        }
        plt::plot(time, output, "b-", {{"label", "output"}});
        plt::xlabel("Time [s]");
        plt::ylabel("y");
        plt::legend("best");
        plt::grid();
        plt::show();    
    }
};
