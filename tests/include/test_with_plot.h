// Author: Filip Dymczyk
// Description : Test with plots utility class.

#pragma once
#include <string>
#include <vector>
#include "base_classes/controller_base.h"
#include "base_classes/object_representation_base.h"
#include "base_classes/signal_base.h"
#include "base_classes/simulation_object_base.h"
#include "control_system.h"

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
    Test_With_Plot(double sim_time) : m_sim_time(sim_time) {}

    void
    test_signal(Signal_Base* signal, std::string signal_plot_title);

    void
    test_closed_loop_control(
        Object_Representation_Base* object, Controller_Base* controller, Signal_Base* input_signal,
        bool const plot_control = false) const;

    void
    test_open_loop_control(
        Object_Representation_Base* object, Controller_Base* controller, Signal_Base* input_signal,
        bool plot_control = false) const;

    void
    test_component(Simulation_Object_Base* component, Signal_Base* input_signal, bool plot_control = false) const;

    template<typename TunerT>
    void
    test_tuner(Signal_Base* input_signal, TunerT tuner, bool plot_control = false) const
    {
        Plotting_Buffers const buffers = simulate_tuner(input_signal, tuner);
        plot_test(buffers, Control_System::Control_Mode::CLOSED_LOOP, plot_control);
    }

    void
    set_sim_time(double sim_time)
    {
        m_sim_time = sim_time;
    }

private:
    double m_sim_time {};

    Plotting_Buffers const
    simulate_signal(Signal_Base* signal);

    Plotting_Buffers const
    simulate_open_closed_loop(
        Object_Representation_Base* object, Controller_Base* controller, Signal_Base* input_signal,
        Control_System::Control_Mode const& control_mode) const;

    Plotting_Buffers const
    simulate_component(Simulation_Object_Base* object, Signal_Base* input_signal) const;

    template<typename TunerT>
    Plotting_Buffers const
    simulate_tuner(Signal_Base* input_signal, TunerT tuner) const
    {
        std::vector<double> time {};
        std::vector<double> set_point {};
        std::vector<double> control {};
        std::vector<double> output {};

        while(input_signal->time() < m_sim_time)
        {
            time.push_back(input_signal->time());
            set_point.push_back(input_signal->get_value());
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
        std::string signal_plot_title = "") const;
};