// Author : Filip Dymczyk
// Description : Class handling inputs parsing.

#pragma once
#include <assert.h>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
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
            case LineEdit_ID::OBJECT_PARAMETERS_LINE_EDIT:
            {
                int const object_parameters_limit = _inputs.get_order() + 1;
                std::vector<double> const object_parameters =
                    parse_vector_parameters(line_edit, object_parameters_limit);
                _inputs.set_object_parameters(object_parameters);
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
            case LineEdit_ID::SIMULATION_TIME_LINE_EDIT:
            {
                double const simulation_time = parse_simulation_time(line_edit);
                _inputs.set_simulation_time(simulation_time);
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
                _inputs.set_simulation_time_step(simulation_time_step.toDouble());
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void
    set_order(int order)
    {
        _inputs.set_order(order);
    }

    // This will need some error protections.
    std::vector<double>
    parse_vector_parameters(QLineEdit* line_edit, int parameters_limit)
    {
        QStringList const parameters_string_list = line_edit->text().split(";", Qt::SkipEmptyParts);
        std::vector<double> parameters {};
        parameters.reserve(parameters_limit);

        std::size_t idx = 1;
        for(auto const& parameter: parameters_string_list)
        {
            parameters.push_back(parameter.toDouble());
            if(idx == parameters_limit)
            {
                break;
            }
            idx++;
        }
        return parameters;
    }

    // This will need some error protections.
    double
    parse_simulation_time(QLineEdit* line_edit)
    {
        return line_edit->text().toDouble();
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
};