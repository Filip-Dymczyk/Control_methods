// Author : Filip Dymczyk
// Description : Dependency handler input parameter container.

#pragma once
#include <cstdint>
#include <vector>
#include "base_classes/signal_base.h"
#include "enums.h"

class Input_Parameters_Container
{
    struct LineEdit_Inputs
    {
        std::vector<double> initial_conditions {0.0, 0.0};
        std::vector<double> object_parameters {1.0, 1.0, 1.0};
        std::vector<double> controller_parameters {1.0, 1.0, 0.0};
        std::vector<std::vector<double>> A_matrix = {{0.0, 1.0}, {-1.0, -1.0}};
        std::vector<double> B_vector              = {0.0, 1.0};
        std::vector<double> C_vector              = {1.0, 0.0};
        double D {0.0};
        double start_time {0.0};
        double scaler {1.0};
        double on_time {5.0};
        double omega {1.0};
        double offset {0.0};
        double duty_cycle {0.5};
        double period {2.0};
        double simulation_time {10.0};
        double measurement_noise_std {0.001};
        double pid_derivative_filtering_coefficient {0.5};
    };

    struct ComboBoxes_Inputs
    {
        Object_Representation object_representation = Object_Representation::EQUATION;
        Control_Mode control_mode                   = Control_Mode::OPEN_LOOP;
        Controller_Type controller_type             = Controller_Type::NONE;
        Input_Signal input_signal                   = Input_Signal::HEAVISIDE;
        Operation_Type operation_type               = Operation_Type::SIMULATION;
        double simulation_time_step {0.01};
    };

public:
    bool
    allowed_to_run() const
    {
        std::size_t const equation_order    = _orders.at(static_cast<std::size_t>(Object_Representation::EQUATION));
        std::size_t const state_space_order = _orders.at(static_cast<std::size_t>(Object_Representation::STATE_SPACE));
        bool const valid_state_space_matrices_sizes = (_line_edit_inputs.A_matrix.size() == state_space_order) &&
                                                      (_line_edit_inputs.A_matrix.at(0).size() == state_space_order) &&
                                                      (_line_edit_inputs.B_vector.size() == state_space_order) &&
                                                      (_line_edit_inputs.C_vector.size() == state_space_order);

        return ((_comboboxes_inputs.object_representation == Object_Representation::EQUATION) &&
                (equation_order == _line_edit_inputs.object_parameters.size() - 1u) &&
                (equation_order == _line_edit_inputs.initial_conditions.size())) ||
               ((_comboboxes_inputs.object_representation == Object_Representation::STATE_SPACE) &&
                valid_state_space_matrices_sizes && (state_space_order == _line_edit_inputs.initial_conditions.size()));
    }

    void
    set_plot_control_signal(bool checked)
    {
        _plot_control_signal = checked;
    }

    void
    set_enable_measurement_noise(bool checked)
    {
        _enable_measurement_noise = checked;
    }

    void
    set_enable_pid_derivative_filtering(bool checked)
    {
        _enable_pid_derivative_filtering = checked;
    }

    void
    set_order(std::size_t order, Object_Representation representation)
    {
        _orders.at(static_cast<std::size_t>(representation)) = order;
    }

    void
    set_initial_conditions(std::vector<double> const& initial_conditions)
    {
        _line_edit_inputs.initial_conditions = initial_conditions;
    }

    void
    set_object_parameters(std::vector<double> const& object_parameters)
    {
        _line_edit_inputs.object_parameters = object_parameters;
    }

    void
    set_A_matrix(std::vector<std::vector<double>> const& A_matrix)
    {
        _line_edit_inputs.A_matrix = A_matrix;
    }

    void
    set_B_vector(std::vector<double> const& B_vector)
    {
        _line_edit_inputs.B_vector = B_vector;
    }

    void
    set_C_vector(std::vector<double> const& C_vector)
    {
        _line_edit_inputs.C_vector = C_vector;
    }

    void
    set_D(double D)
    {
        _line_edit_inputs.D = D;
    }

    void
    set_controller_parameters(std::vector<double> const& controller_parameters)
    {
        _line_edit_inputs.controller_parameters = controller_parameters;
    }

    void
    set_start_time(double start_time)
    {
        _line_edit_inputs.start_time = start_time;
    }

    void
    set_scaler(double scaler)
    {
        _line_edit_inputs.scaler = scaler;
    }

    void
    set_on_time(double on_time)
    {
        _line_edit_inputs.on_time = on_time;
    }

    void
    set_omega(double omega)
    {
        _line_edit_inputs.omega = omega;
    }

    void
    set_offset(double offset)
    {
        _line_edit_inputs.offset = offset;
    }

    void
    set_duty_cycle(double duty_cycle)
    {
        _line_edit_inputs.duty_cycle = duty_cycle;
    }

    void
    set_period(double period)
    {
        _line_edit_inputs.period = period;
    }

    void
    set_simulation_time(double simulation_time)
    {
        _line_edit_inputs.simulation_time = simulation_time;
    }

    void
    set_measurement_noise_std(double measurement_noise_std)
    {
        _line_edit_inputs.measurement_noise_std = measurement_noise_std;
    }

    void
    set_pid_derivative_filtering_coefficient(double filtering_coefficient)
    {
        _line_edit_inputs.pid_derivative_filtering_coefficient = filtering_coefficient;
    }

    void
    set_simulation_time_step(double simulation_time_step)
    {
        _comboboxes_inputs.simulation_time_step = simulation_time_step;
    }

    void
    set_object_representation(Object_Representation const& object_representation)
    {
        _comboboxes_inputs.object_representation = object_representation;
    }

    void
    set_control_mode(Control_Mode const& control_mode)
    {
        _comboboxes_inputs.control_mode = control_mode;
    }

    void
    set_controller_type(Controller_Type const& controller_type)
    {
        _comboboxes_inputs.controller_type = controller_type;
    }

    void
    set_input_signal(Input_Signal const& input_signal)
    {
        _comboboxes_inputs.input_signal = input_signal;
    }

    void
    set_operation_type(Operation_Type const& operation_type)
    {
        _comboboxes_inputs.operation_type = operation_type;
    }

    bool
    get_plot_control_signal() const
    {
        return _plot_control_signal;
    }

    bool
    get_enable_measurement_noise() const
    {
        return _enable_measurement_noise;
    }

    bool
    get_enable_pid_derivative_filtering() const
    {
        return _enable_pid_derivative_filtering;
    }

    std::vector<std::size_t> const
    get_orders() const
    {
        return _orders;
    }

    std::vector<double> const&
    get_initial_conditions() const
    {
        return _line_edit_inputs.initial_conditions;
    }

    std::vector<double> const&
    get_object_parameters() const
    {
        return _line_edit_inputs.object_parameters;
    }

    std::vector<std::vector<double>> const&
    get_A_matrix() const
    {
        return _line_edit_inputs.A_matrix;
    }

    std::vector<double> const&
    get_B_vector() const
    {
        return _line_edit_inputs.B_vector;
    }

    std::vector<double> const&
    get_C_vector() const
    {
        return _line_edit_inputs.C_vector;
    }

    double
    get_D() const
    {
        return _line_edit_inputs.D;
    }

    std::vector<double> const&
    get_controller_parameters() const
    {
        return _line_edit_inputs.controller_parameters;
    }

    double
    get_simulation_time() const
    {
        return _line_edit_inputs.simulation_time;
    }

    double
    get_measurement_noise_std() const
    {
        return _line_edit_inputs.measurement_noise_std;
    }

    double
    get_pid_derivative_filtering_coefficient() const
    {
        return _line_edit_inputs.pid_derivative_filtering_coefficient;
    }

    double
    get_simulation_time_step() const
    {
        return _comboboxes_inputs.simulation_time_step;
    }

    Object_Representation
    get_object_representation() const
    {
        return _comboboxes_inputs.object_representation;
    }

    Control_Mode
    get_control_mode() const
    {
        return _comboboxes_inputs.control_mode;
    }

    Controller_Type
    get_controller_type() const
    {
        return _comboboxes_inputs.controller_type;
    }

    Input_Signal
    get_input_signal() const
    {
        return _comboboxes_inputs.input_signal;
    }

    Signal_Base::Signal_Basic_Parameters
    get_input_signal_basic_parameters() const
    {
        return {_line_edit_inputs.start_time, _line_edit_inputs.scaler};
    }

    std::array<double, 5>
    get_input_signal_advanced_parameters() const
    {
        return {
            _line_edit_inputs.on_time, _line_edit_inputs.omega, _line_edit_inputs.offset, _line_edit_inputs.period,
            _line_edit_inputs.duty_cycle};
    }

    Operation_Type
    get_operation_type() const
    {
        return _comboboxes_inputs.operation_type;
    }

private:
    bool _plot_control_signal {false};
    bool _enable_measurement_noise {false};
    bool _enable_pid_derivative_filtering {false};
    std::vector<std::size_t> _orders {2u, 2u};
    LineEdit_Inputs _line_edit_inputs {};
    ComboBoxes_Inputs _comboboxes_inputs {};
};