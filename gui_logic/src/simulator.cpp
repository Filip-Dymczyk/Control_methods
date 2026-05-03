#include "simulator.h"

Simulator::Simulator(QWidget* parent) : QObject(parent), m_plotter(new Plotter(parent))
{
    connect(m_plotter, &Plotter::toggle_stop_simulation, this, &Simulator::toggle_stop_simulation);
}

void
Simulator::update(Input_Parameters_Container const& input_parameters)
{
    m_simulation_time = input_parameters.get_simulation_time();
    m_plotter->set_plot_control_signal(input_parameters.get_plot_control_signal());

    double const simulation_time_step = input_parameters.get_simulation_time_step();
    m_control.set_object(
        input_parameters.get_orders(), simulation_time_step, input_parameters.get_object_representation(),
        input_parameters.get_initial_conditions(), input_parameters.get_object_parameters(),
        input_parameters.get_control_signal_scaler(),
        {input_parameters.get_A_matrix(), input_parameters.get_B_vector(), input_parameters.get_C_vector(),
         input_parameters.get_D()});
    m_control.set_control_mode(input_parameters.get_control_mode());
    m_control.set_controller(
        simulation_time_step, input_parameters.get_controller_type(), input_parameters.get_controller_parameters());
    if(input_parameters.get_controller_type() == Controller_Type::PID)
    {
        m_control.enable_pid_derivative_filtering(input_parameters.get_enable_pid_derivative_filtering());
        m_control.set_pid_derivative_filtering_coefficient(input_parameters.get_pid_derivative_filtering_coefficient());
    }
    m_control.set_signal(
        simulation_time_step, input_parameters.get_input_signal(), input_parameters.get_input_signal_basic_parameters(),
        input_parameters.get_input_signal_advanced_parameters());
    m_control.set_operation_type(input_parameters.get_operation_type());
    m_control.enable_measurement_noise(input_parameters.get_enable_measurement_noise());
    m_control.set_measurement_noise_std(input_parameters.get_measurement_noise_std());
    if(m_control.get_operation_type() == Operation_Type::TUNING)
    {
        m_control.set_RLS_forgetting_factor(input_parameters.get_RLS_forgetting_factor());
    }
}

void
Simulator::run()
{
    reset();
    m_plotter->show_chart(m_control.get_control_mode(), m_simulation_time);
    while(m_control.get_time() < m_simulation_time)
    {
        if(m_break_simulation || !m_plotter->is_window_open())
        {
            break;
        }

        if(!m_stop_simulation)
        {
            m_plotter->update(
                m_control.get_time(), m_control.get_setpoint(), m_control.get_control_value(),
                m_control.get_object_value());

            m_control.update();
        }
        QApplication::processEvents();
    }

    if(m_control.get_operation_type() == Operation_Type::TUNING)
    {
        Q_EMIT update_pid_parameters_line_edit_after_tuning(m_control.get_pid_parameters());
    }
}

void
Simulator::break_simulation()
{
    m_break_simulation = true;
}

void
Simulator::reset()
{
    m_control.reset();
    m_plotter->reset();
    m_stop_simulation = false;  // Restores the state after the toggling from plotter reset.
}

void
Simulator::toggle_stop_simulation()
{
    m_stop_simulation = !m_stop_simulation;
}