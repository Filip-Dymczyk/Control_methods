// Author: Filip Dymczyk
// Description : Tests with plots.

#pragma once
#include <math.h>
#include <string>
#include "base_classes/controller_base.h"
#include "base_classes/object_representation_base.h"
#include "base_classes/signal_base.h"
#include "base_classes/simulation_object_base.h"
#include "control_system.h"
#include "matplotlibcpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;

// NOTE: Allows to test components and control systems by plotting: set point, output and optionally - control value.
class Test_With_Plot
{
    struct Plotting_Buffers
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};
    };

public:
    Test_With_Plot(double sim_time) : _sim_time(sim_time) {}

    void
    test_signal(Signal_Base* signal, std::string signal_plot_title)
    {
        signal->reset();
        Plotting_Buffers const buffers = simulate_signal(signal);

        plot_test(buffers, Control_System::Control_Mode::NONE, false, signal_plot_title);
    }

    void
    test_closed_loop_control(
        Object_Representation_Base* object, Controller_Base* controller, Signal_Base* input_signal,
        bool const plot_control = false) const
    {
        Plotting_Buffers const buffers =
            simulate_open_closed_loop(object, controller, input_signal, Control_System::Control_Mode::CLOSED_LOOP);

        plot_test(buffers, Control_System::Control_Mode::CLOSED_LOOP, plot_control);
    }

    void
    test_open_loop_control(
        Object_Representation_Base* object, Controller_Base* controller, Signal_Base* input_signal,
        bool plot_control = false) const
    {
        Plotting_Buffers const buffers =
            simulate_open_closed_loop(object, controller, input_signal, Control_System::Control_Mode::OPEN_LOOP);

        plot_test(buffers, Control_System::Control_Mode::OPEN_LOOP, plot_control);
    }

    void
    test_component(Simulation_Object_Base* component, Signal_Base* input_signal, bool plot_control = false) const
    {
        Plotting_Buffers const buffers = simulate_component(component, input_signal);

        plot_test(buffers, Control_System::Control_Mode::NONE, plot_control);
    }

    template<typename TunerT>
    void
    test_tuner(Signal_Base* input_signal, TunerT tuner, bool plot_control = false) const
    {
        Plotting_Buffers const buffers = simulate_tuner<TunerT>(input_signal, tuner);

        plot_test(buffers, Control_System::Control_Mode::CLOSED_LOOP, plot_control);
    }

    void
    set_sim_time(double sim_time)
    {
        _sim_time = sim_time;
    }

private:
    double _sim_time {};

    Plotting_Buffers const
    simulate_signal(Signal_Base* signal)
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};

        while(signal->time() < _sim_time)
        {
            time.push_back(signal->time());
            output.push_back(signal->get_value());
            signal->update();
        }
        return {time, set_point, control, output};
    }

    Plotting_Buffers const
    simulate_open_closed_loop(
        Object_Representation_Base* object, Controller_Base* controller, Signal_Base* input_signal,
        Control_System::Control_Mode const& control_mode) const
    {
        input_signal->reset();
        Control_System control_loop {object, controller, control_mode};
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};

        while(input_signal->time() < _sim_time)
        {
            time.push_back(input_signal->time());
            set_point.push_back(input_signal->get_value());
            control.push_back(control_loop.get_control());
            output.push_back(control_loop.get_output());
            control_loop.update(input_signal->get_value());
            input_signal->update();
        }
        return {time, set_point, control, output};
    }

    Plotting_Buffers const
    simulate_component(Simulation_Object_Base* object, Signal_Base* input_signal) const
    {
        input_signal->reset();
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> output {};

        while(input_signal->time() < _sim_time)
        {
            time.push_back(input_signal->time());
            set_point.push_back(input_signal->get_value());
            output.push_back(object->get_value());
            object->update(input_signal->get_value());
            input_signal->update();
        }
        return {time, set_point, {}, output};
    }

    template<typename TunerT>
    Plotting_Buffers const
    simulate_tuner(Signal_Base* input_signal, TunerT tuner) const
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};

        while(input_signal->time() < _sim_time)
        {
            time.push_back(input_signal->time());
            set_point.push_back(tuner.get_set_point());
            control.push_back(tuner.get_control());
            output.push_back(tuner.get_output());
            tuner.update(input_signal->get_value());
            input_signal->update();
        }
        return {time, set_point, control, output};
    }

    void
    plot_test(
        Plotting_Buffers const& buffers, Control_System::Control_Mode const& control_mode, bool plot_control,
        std::string signal_plot_title = "") const
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
                case Control_System::Control_Mode::CLOSED_LOOP:
                {
                    plt::title("Closed loop control system response");
                    break;
                }
                case Control_System::Control_Mode::OPEN_LOOP:
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
