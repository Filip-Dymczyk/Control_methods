// Author: Filip Dymczyk
// Description : Tests with plots.

#pragma once
#include <math.h>
#include <string>
#include "matplotlibcpp/matplotlibcpp.h"
#include "signals/signals.h"

namespace plt = matplotlibcpp;

// NOTE: Allows to components and control systems by plotting: set point, output and optionally - control value.
class TestWithPlot
{
    enum class ControlMode : uint8_t
    {
        NONE,
        OPEN_LOOP,
        CLOSED_LOOP
    };

    struct PlottingBuffers
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
    };

public:
    TestWithPlot(double sim_time) : _sim_time(sim_time) {}
    
    void
    test_signal(Signal * signal, std::string signal_plot_title)
    {
        signal -> reset();
        PlottingBuffers const buffers = simulate_signal(signal);
        
        plot_test(buffers, ControlMode::NONE, false, signal_plot_title);
    }

    template<typename ObjectT, typename ControllerT>
    void
    test_closed_loop_control(ObjectT object, ControllerT controller, Signal* input_signal, bool const plot_control = false) const 
    {
        PlottingBuffers const buffers = simulate_open_closed_loop(object, controller, input_signal, ControlMode::CLOSED_LOOP);

        plot_test(buffers, ControlMode::CLOSED_LOOP, plot_control);
    }

    template<typename ObjectT, typename ControllerT>
    void
    test_open_loop_control(ObjectT object, ControllerT controller, Signal * input_signal, bool plot_control = false) const 
    {
        PlottingBuffers const buffers = simulate_open_closed_loop(object, controller, input_signal, ControlMode::OPEN_LOOP);

        plot_test(buffers, ControlMode::OPEN_LOOP, plot_control);
    }

    template<typename ComponentT>
    void
    test_component(ComponentT component, Signal * input_signal, bool plot_control = false) const 
    {
        PlottingBuffers const buffers = simulate_component(component, input_signal);

        plot_test(buffers, ControlMode::NONE, plot_control);
    }

    template<typename TunerT>
    void
    test_tuner(TunerT tuner) const 
    {
        PlottingBuffers const buffers = simulate_tuner<TunerT>(tuner);

        plot_test(buffers, ControlMode::CLOSED_LOOP, false);
    }

    void
    set_sim_time(double sim_time)
    {
        _sim_time = sim_time;
    }
private:
    double _sim_time {};

    PlottingBuffers const
    simulate_signal(Signal * signal)
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
        
        while(signal -> time() < _sim_time)
        {
            time.push_back(signal -> time());
            output.push_back(signal -> get_value());
            signal -> update();
        }  
        return {time, set_point, control, output};
    }
    
    template<typename ObjectT, typename ControllerT>
    PlottingBuffers const
    simulate_open_closed_loop(ObjectT object, ControllerT controller, Signal * input_signal, ControlMode const & control_mode) const 
    {
        input_signal -> reset();
        ControlSystem<ObjectT, ControllerT> control_loop {object, controller, control_mode};
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
        
        while(input_signal -> time() < _sim_time)
        {
            time.push_back(input_signal -> time());
            control_loop.update(input_signal -> get_value());
            set_point.push_back(input_signal -> get_value());
            control.push_back(control_loop.get_control());
            output.push_back(control_loop.get_output());
            input_signal -> update();
        }  
        return {time, set_point, control, output};
    }

    template<typename ComponentT>
    PlottingBuffers const
    simulate_component(ComponentT object, Signal * input_signal) const 
    {
        input_signal -> reset();
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> output {};

        while(input_signal -> time() < _sim_time)
        {
            time.push_back(input_signal -> time());
            object.update(input_signal -> get_value());   
            set_point.push_back(input_signal -> get_value());
            output.push_back(object.get_value());
            input_signal -> update();
        }  
        return {time, set_point, {}, output};
    }

    template<typename TunerT>
    PlottingBuffers const
    simulate_tuner(TunerT tuner) const 
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
        
        while(tuner.get_time() < _sim_time)
        {
            time.push_back(tuner.get_time());
            tuner.update();
            set_point.push_back(tuner.get_set_point());
            control.push_back(tuner.get_control());
            output.push_back(tuner.get_output());
        }  
        return {time, set_point, control, output};
    }

    void
    plot_test(PlottingBuffers const & buffers, ControlMode const & control_mode, bool plot_control, std::string signal_plot_title = "") const 
    {
        plt::figure();
        if(!signal_plot_title.empty())
        {
            plt::title(signal_plot_title);
        }
        else
        {
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
        }
        
        if(signal_plot_title.empty())
        {
            plt::plot(buffers.time, buffers.set_point, "r-", {{"label", "set point"}});
        }
        if(plot_control)
        {
            plt::plot(buffers.time, buffers.control, "y-", {{"label", "control"}});
        }
        plt::plot(buffers.time, buffers.output, "b-", {{"label", "output"}});
        plt::xlabel("Time [s]");
        plt::ylabel("y");
        plt::legend("best");
        plt::grid();
        plt::show();    
    }
};
