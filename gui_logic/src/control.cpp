#include "control.h"

Control::Control()
    : m_differential_equation_representation_object(TIME_STEP, ORDER),
      m_state_space_representation_object(TIME_STEP, ORDER),
      m_pid_controller(TIME_STEP),
      m_bang_bang_controller(TIME_STEP),
      m_heaviside(TIME_STEP),
      m_ramp(TIME_STEP),
      m_rect(TIME_STEP),
      m_sine_wave(TIME_STEP),
      m_pulse_wave(TIME_STEP),
      m_no_signal(TIME_STEP),
      m_selected_object(nullptr),
      m_selected_controller(nullptr),
      m_selected_input_signal(&m_no_signal),
      m_regression(),
      m_system(m_selected_object, Control_System::Control_Mode::OPEN_LOOP),
      m_tuner(m_system, m_regression),
      m_operation_type(Operation_Type::SIMULATION)
{
}

void
Control::set_object(
    std::vector<std::size_t> orders, double time_step, Object_Representation object_representation,
    std::vector<double> const& initial_conditions, std::vector<double> const& object_parameters,
    double control_signal_scaler, Object_Representation_Base::State_Space_Matrices const& matrices)
{
    switch(object_representation)
    {
        case Object_Representation::EQUATION:
        {
            m_differential_equation_representation_object.set_control_signal_scaler(control_signal_scaler);
            m_differential_equation_representation_object.set_order(orders[static_cast<std::size_t>(
                Object_Representation::EQUATION)]);  // Order needs to be set prior to setting parameters.
            m_differential_equation_representation_object.set_parameters(object_parameters);

            m_selected_object = &m_differential_equation_representation_object;
            break;
        }
        case Object_Representation::STATE_SPACE:
        {
            m_state_space_representation_object.set_order(orders[static_cast<std::size_t>(
                Object_Representation::STATE_SPACE)]);  // Order needs to be set prior to setting matrices.
            m_state_space_representation_object.set_parameters(matrices);

            m_selected_object = &m_state_space_representation_object;
            break;
        }
        default:
            assert(false);
            break;
    }

    m_selected_object->set_initial_conditions(initial_conditions);
    m_selected_object->set_time_step(time_step);
    m_system.set_object(m_selected_object);
}

void
Control::set_control_mode(Control_Mode control_mode)
{
    m_system.set_control_mode(static_cast<Control_System::Control_Mode>(control_mode));
}

void
Control::set_controller(
    double time_step, Controller_Type controller_type, std::vector<double> const& controller_parameters)
{
    switch(controller_type)
    {
        case Controller_Type::BANG_BANG:
        {
            m_selected_controller = &m_bang_bang_controller;
            break;
        }
        case Controller_Type::PID:
        {
            m_selected_controller = &m_pid_controller;
            break;
        }
        case Controller_Type::NONE:
        {
            m_selected_controller = nullptr;
            break;
        }
        default:
            break;
    }

    if(m_selected_controller != nullptr)
    {
        m_selected_controller->set_time_step(time_step);
        m_selected_controller->set_parameters(controller_parameters);
    }
    m_system.set_controller(m_selected_controller);
}

void
Control::set_signal(
    double time_step, Input_Signal input_signal, Signal_Base::Signal_Basic_Parameters const& signal_basic_parameters,
    std::array<double, 5> const& advanced_parameters)
{
    switch(input_signal)
    {
        case Input_Signal::NO_SIGNAL:
        {
            m_selected_input_signal = &m_no_signal;
            break;
        }
        case Input_Signal::HEAVISIDE:
        {
            m_selected_input_signal = &m_heaviside;
            break;
        }
        case Input_Signal::RAMP:
        {
            m_selected_input_signal = &m_ramp;
            break;
        }
        case Input_Signal::RECTANGLE:
        {
            m_rect.set_on_time(
                advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::ON_TIME)));
            m_selected_input_signal = &m_rect;
            break;
        }
        case Input_Signal::SINE_WAVE:
        {
            m_sine_wave.set_omega(
                advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::OMEGA)));
            m_sine_wave.set_offset(
                advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::OFFSET)));
            m_selected_input_signal = &m_sine_wave;
            break;
        }
        case Input_Signal::PULSE_WAVE:
        {
            m_pulse_wave.set_period(
                advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::PERIOD)));
            m_pulse_wave.set_duty_cycle(
                advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::DUTY_CYCLE)));
            m_selected_input_signal = &m_pulse_wave;
            break;
        }
        default:
            assert(false);
            break;
    }

    m_selected_input_signal->set_time_step(time_step);
    m_selected_input_signal->set_parameters(signal_basic_parameters);
}

void
Control::set_operation_type(Operation_Type operation_type)
{
    m_operation_type = operation_type;
}

void
Control::enable_measurement_noise(bool enable)
{
    assert(m_selected_object != nullptr);
    m_selected_object->enable_measurement_noise(enable);
}

void
Control::set_measurement_noise_std(double measurement_noise_std)
{
    assert(m_selected_object != nullptr);
    m_selected_object->set_measurement_noise_std(measurement_noise_std);
}

void
Control::set_RLS_forgetting_factor(double forgetting_factor)
{
    m_tuner.set_RLS_forgetting_factor(forgetting_factor);
}

void
Control::enable_pid_derivative_filtering(bool enable)
{
    m_pid_controller.enable_derivative_filtering(enable);
}

void
Control::set_pid_derivative_filtering_coefficient(double filtering_coefficient)
{
    m_pid_controller.set_derivative_filtering_coefficient(filtering_coefficient);
}

double
Control::get_time() const
{
    assert(m_selected_input_signal != nullptr);
    return m_selected_input_signal->time();
}

double
Control::get_setpoint() const
{
    assert(m_selected_input_signal != nullptr);
    return m_selected_input_signal->get_value();
}

double
Control::get_control_value() const
{
    return m_system.get_control();
}

double
Control::get_object_value() const
{
    return m_system.get_output();
}

void
Control::update()
{
    assert(m_selected_input_signal != nullptr);

    double const input = m_selected_input_signal->get_value();
    switch(m_operation_type)
    {
        case Operation_Type::TUNING:
            m_tuner.update(input);
            break;
        case Operation_Type::SIMULATION:
            m_system.update(input);
            break;
        default:
            assert(false);
            break;
    }

    m_selected_input_signal->update();
}

Control_System::Control_Mode
Control::get_control_mode() const
{
    return m_system.get_control_mode();
}

Operation_Type
Control::get_operation_type() const
{
    return m_operation_type;
}

std::array<double, 3>
Control::get_pid_parameters() const
{
    return m_pid_controller.get_parameters();
}

void
Control::reset()
{
    switch(m_operation_type)
    {
        case Operation_Type::TUNING:
            m_tuner.reset();
            m_tuner.set_initial_pid_parameters(m_pid_controller.get_parameters());
            break;
        case Operation_Type::SIMULATION:
            m_system.reset();
            break;
        default:
            assert(false);
            break;
    }

    assert(m_selected_input_signal != nullptr);
    m_selected_input_signal->reset();
}