// Author : Filip Dymczyk
// Description : Class handling inputs parsing.

#pragma once
#include <assert.h>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <limits>
#include "enums.h"
#include "input_parameters_container.h"

class Inputs_Parser : public QObject
{
    Q_OBJECT

public:
    void
    parse_line_edit_id(QLineEdit* line_edit, LineEdit_ID line_edit_id)
    {
        switch(line_edit_id)
        {
            case LineEdit_ID::INITIAL_CONDITIONS_LINE_EDIT:
            {
                std::vector<double> const initial_conditions = parse_vector_parameters(line_edit);
                _inputs.set_initial_conditions(initial_conditions);
                break;
            }
            case LineEdit_ID::OBJECT_PARAMETERS_LINE_EDIT:
            {
                std::vector<double> const object_parameters = parse_vector_parameters(line_edit);
                _inputs.set_order(object_parameters.size() - 1u, Object_Representation::EQUATION);
                _inputs.set_object_parameters(object_parameters);
                break;
            }
            case LineEdit_ID::A_MATRIX_LINE_EDIT:
            {
                std::vector<std::vector<double>> const& A_matrix = parse_matrix_parameters(line_edit);
                _inputs.set_order(A_matrix.size(), Object_Representation::STATE_SPACE);
                _inputs.set_A_matrix(A_matrix);
                break;
            }
            case LineEdit_ID::B_VECTOR_LINE_EDIT:
            {
                std::vector<double> const B_vector = parse_vector_parameters(line_edit, -1, false, ";");
                _inputs.set_B_vector(B_vector);
                break;
            }
            case LineEdit_ID::C_VECTOR_LINE_EDIT:
            {
                std::vector<double> const C_vector = parse_vector_parameters(line_edit);
                _inputs.set_C_vector(C_vector);
                break;
            }
            case LineEdit_ID::D_LINE_EDIT:
            {
                double const D = parse_single_number_line_edit(line_edit);
                _inputs.set_D(D);
                break;
            }
            case LineEdit_ID::CONTROLLER_PARAMETERS_LINE_EDIT:
            {
                int const controller_parameters_limit = 3;  // PID and Bang-Bang Controllers.
                std::vector<double> const controller_parameters =
                    parse_vector_parameters(line_edit, controller_parameters_limit);
                _inputs.set_controller_parameters(controller_parameters);
                break;
            }
            case LineEdit_ID::START_TIME_LINE_EDIT:
            {
                double const start_time = parse_single_number_line_edit(line_edit);
                _inputs.set_start_time(start_time);
                break;
            }
            case LineEdit_ID::SCALER_LINE_EDIT:
            {
                double const scaler = parse_single_number_line_edit(
                    line_edit, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
                _inputs.set_scaler(scaler);
                break;
            }
            case LineEdit_ID::ON_TIME_LINE_EDIT:
            {
                double const on_time = parse_single_number_line_edit(line_edit);
                _inputs.set_on_time(on_time);
                break;
            }
            case LineEdit_ID::OMEGA_LINE_EDIT:
            {
                double const omega = parse_single_number_line_edit(line_edit);
                _inputs.set_omega(omega);
                break;
            }
            case LineEdit_ID::OFFSET_LINE_EDIT:
            {
                double const offset = parse_single_number_line_edit(
                    line_edit, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
                _inputs.set_offset(offset);
                break;
            }
            case LineEdit_ID::PERIOD_LINE_EDIT:
            {
                double const period = parse_single_number_line_edit(line_edit);
                _inputs.set_period(period);
                break;
            }
            case LineEdit_ID::DUTY_CYCLE_LINE_EDIT:
            {
                double const duty_cycle_percent         = parse_single_number_line_edit(line_edit, 0.0, 100.0);
                static double const percent_to_fraction = 0.01;
                _inputs.set_duty_cycle(duty_cycle_percent * percent_to_fraction);
                break;
            }
            case LineEdit_ID::SIMULATION_TIME_LINE_EDIT:
            {
                double const simulation_time = parse_single_number_line_edit(line_edit);
                _inputs.set_simulation_time(simulation_time);
                break;
            }
            case LineEdit_ID::MEASUREMENT_NOISE_LINE_EDIT:
            {
                double const measurement_noise_std = parse_single_number_line_edit(line_edit, 0.0);
                _inputs.set_measurement_noise_std(measurement_noise_std);
                break;
            }
            case LineEdit_ID::PID_DERIVATIVE_FILTERING_COEFFICIENT_LINE_EDIT:
            {
                double const filtering_coefficient = parse_single_number_line_edit(line_edit, 0.0, 1.0);
                _inputs.set_pid_derivative_filtering_coefficient(filtering_coefficient);
                break;
            }
            default:
                break;
        }
    }

    void
    parse_combobox_id(QComboBox* combobox, ComboBox_ID combo_box_id)
    {
        int const current_index = combobox->currentIndex();

        switch(combo_box_id)
        {
            case ComboBox_ID::OBJECT_REPRESENTATION:
            {
                _inputs.set_object_representation(static_cast<Object_Representation>(current_index));
                break;
            }
            case ComboBox_ID::CONTROL_MODE:
            {
                _inputs.set_control_mode(static_cast<Control_Mode>(current_index));
                break;
            }
            case ComboBox_ID::CONTROLLER_TYPE:
            {
                Controller_Type const new_controller_type = static_cast<Controller_Type>(current_index);
                check_disable_enable_controller_parameters(new_controller_type);

                _inputs.set_controller_type(new_controller_type);
                break;
            }
            case ComboBox_ID::INPUT_SIGNAL:
            {
                _inputs.set_input_signal(static_cast<Input_Signal>(current_index));
                break;
            }
            case ComboBox_ID::OPERATION_TYPE:
            {
                _inputs.set_operation_type(static_cast<Operation_Type>(current_index));
                break;
            }
            case ComboBox_ID::SIMULATION_TIME_STEP:
            {
                QVariant const simulation_time_step = combobox->currentData();
                bool ok;
                double const value = simulation_time_step.toDouble(&ok);
                if(!ok)
                {
                    return;
                }

                _inputs.set_simulation_time_step(value);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    std::vector<double>
    parse_vector_parameters(
        QLineEdit* line_edit, int parameters_count = -1, bool parsing_matrix = false, QString splitter = ",")
    {
        QString text = line_edit->text().trimmed();
        if(!parsing_matrix && (!text.startsWith('[') || !text.endsWith(']')))
        {
            Q_EMIT unable_to_parse(text);
            return {};
        }

        if(!parsing_matrix)
        {
            text = text.mid(1, text.length() - 2);  // Get rid of brackets.
        }
        QStringList const parameters_string_list    = text.split(splitter, Qt::SkipEmptyParts);
        std::size_t const entered_parameters_number = parameters_string_list.size();
        std::vector<double> parameters {};

        bool ok;
        std::size_t idx = 1;
        for(auto const& parameter: parameters_string_list)
        {
            double const value = parameter.toDouble(&ok);
            if(!ok)
            {
                Q_EMIT unable_to_parse(parameter);
                return {};
            }

            parameters.push_back(value);
            if(parameters_count > 0 && idx == parameters_count)
            {
                break;
            }
            idx++;
        }

        if(parameters_count > 0)
        {
            if(entered_parameters_number > parameters_count)
            {
                Q_EMIT too_many_input_parameters();

                line_edit->setText(get_new_line_edit_text_from_parameters(parameters));
            }
            else if(entered_parameters_number < parameters_count)
            {
                Q_EMIT too_few_input_parameters();

                QString new_text = get_new_line_edit_text_from_parameters(parameters);
                if(parameters.size() > 0)
                {
                    new_text += splitter;  // Avoiding trailing splitter if line edit was empty.
                }

                std::size_t const range = parameters_count - entered_parameters_number;
                for(std::size_t i = 0; i < range; i++)
                {
                    double const default_val = 0.0;
                    parameters.push_back(default_val);
                    new_text += QString::number(default_val, 'f', 1);
                    if(i < range - 1)
                    {
                        new_text += splitter;
                    }
                }

                line_edit->setText(new_text);
            }
        }
        return parameters;
    }

    std::vector<std::vector<double>>
    parse_matrix_parameters(QLineEdit* line_edit)
    {
        QString text = line_edit->text().trimmed();
        if(!text.startsWith('[') || !text.endsWith(']'))
        {
            Q_EMIT unable_to_parse(text);
            return {};
        }

        text                                     = text.mid(1, text.length() - 2);  // Get rid of brackets.
        QStringList const parameters_string_list = text.split(";", Qt::SkipEmptyParts);

        std::vector<std::vector<double>> matrix {};
        for(auto const& text: parameters_string_list)
        {
            QLineEdit text_line_edit      = QLineEdit(text);
            std::vector<double> const row = parse_vector_parameters(&text_line_edit, -1, true);
            if(row.empty())
            {
                return {};
            }

            matrix.emplace_back(row);
        }
        return matrix;
    }

    double
    parse_single_number_line_edit(
        QLineEdit* line_edit, double lower_limit = 0.0, double upper_limit = std::numeric_limits<double>::max())
    {
        bool ok;
        double const value = line_edit->text().toDouble(&ok);
        if(!ok)
        {
            Q_EMIT unable_to_parse(line_edit->text());
            line_edit->setText(QString::number(0.0));
            return 0.0;
        }

        if(value != 0.0 && value < lower_limit)
        {
            Q_EMIT value_below_lower_limit(lower_limit);
            line_edit->setText(QString::number(lower_limit));
            return lower_limit;
        }

        if(value > upper_limit)
        {
            Q_EMIT value_above_upper_limit(upper_limit);
            line_edit->setText(QString::number(upper_limit));
            return upper_limit;
        }
        return value;
    }

    void
    set_plot_control_signal(bool checked)
    {
        _inputs.set_plot_control_signal(checked);
    }

    void
    set_enable_measurement_noise(bool checked)
    {
        _inputs.set_enable_measurement_noise(checked);
    }

    void
    set_enable_pid_derivative_filtering(bool checked)
    {
        _inputs.set_enable_pid_derivative_filtering(checked);
    }

    Input_Parameters_Container const&
    get_input_parameters() const
    {
        return _inputs;
    }

Q_SIGNALS:
    void
    disable_controller_parameters();

    void
    enable_controller_parameters();

    void
    too_many_input_parameters();

    void
    too_few_input_parameters();

    void
    unable_to_parse(QString text);

    void
    value_below_lower_limit(double limit);

    void
    value_above_upper_limit(double limit);

private:
    Input_Parameters_Container _inputs {};

    void
    check_disable_enable_controller_parameters(Controller_Type const& new_controller_type)
    {
        Controller_Type const previous_controller_type = _inputs.get_controller_type();
        if((previous_controller_type == Controller_Type::PID ||
            previous_controller_type == Controller_Type::BANG_BANG) &&
           new_controller_type == Controller_Type::NONE)
        {
            Q_EMIT disable_controller_parameters();
        }
        else if(
            previous_controller_type == Controller_Type::NONE &&
            (new_controller_type == Controller_Type::PID || new_controller_type == Controller_Type::BANG_BANG))
        {
            Q_EMIT enable_controller_parameters();
        }
    }

    QString
    get_new_line_edit_text_from_parameters(std::vector<double> const& parameters)
    {
        std::size_t const range = parameters.size();
        QString new_text {};
        for(std::size_t i = 0; i < range; i++)
        {
            QString number_str = QString::number(parameters.at(i));
            if(!number_str.contains("."))
            {
                number_str += ".0";
            }

            new_text += number_str;
            if(i < range - 1)
            {
                new_text += "|";
            }
        }
        return new_text;
    }
};