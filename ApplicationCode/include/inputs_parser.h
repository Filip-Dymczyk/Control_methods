// Author : Filip Dymczyk
// Description : Class handling inputs parsing.

#pragma once
#include <assert.h>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLineEdit>

#include "enums.h"
#include "input_parameters_container.h"

class Inputs_Parser
{
public:
    bool
    parse_button_id(Button_ID const& button_id, QWidget* parent)
    {
        bool is_run = false;
        switch (button_id)
        {
            case Button_ID::ORDER_BUTTON:
            {
                set_order(parent);
                break;
            }
            case Button_ID::OBJECT_PARAMETERS_BUTTON:
            {
                set_object_parameters(parent);
                break;
            }
            case Button_ID::CONTROLLER_PARAMETERS_BUTTON:
            {
                set_controller_parameters(parent);
                break;
            }
            case Button_ID::SIMULATION_PARAMETERS_BUTTON:
            {
                set_simulation_parameters(parent);
                break;
            }
            case Button_ID::RUN_BUTTON:
            {
                _inputs.set_run_flag(true);
                is_run = true;
                break;
            }
            default:
            {
                break;
            }
        }
        return is_run;
    }

    void
    parse_combo_box_id(Combo_Box_ID const& combo_box_id, int current_index)
    {
        switch (combo_box_id)
        {
            case Combo_Box_ID::OBJECT_REPRESENTATION:
            {
                _inputs.set_object_representation(static_cast<Object_Representation>(current_index));
                break;
            }
            case Combo_Box_ID::CONTROL_MODE:
            {
                _inputs.set_control_mode(static_cast<Control_Mode>(current_index));
                break;
            }
            case Combo_Box_ID::CONTROLLER_TYPE:
            {
                _inputs.set_controller_type(static_cast<Controller_Type>(current_index));
                break;
            }
            case Combo_Box_ID::INPUT_SIGNAL:
            {
                _inputs.set_input_signal(static_cast<Input_Signal>(current_index));
                break;
            }
            case Combo_Box_ID::OPERATION_TYPE:
            {
                _inputs.set_operation_type(static_cast<Operation_Type>(current_index));
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void
    set_order(QWidget* parent)
    {
        if(parent == nullptr)
        {
            assert(false);
            return;
        }
        QSpinBox const* const order_spin_box = parent -> findChild<QSpinBox*>("order");

        if(order_spin_box == nullptr)
        {
            assert(false);
            return;
        }
        _inputs.set_order(order_spin_box->value());
    }

    void
    set_object_parameters(QWidget* parent)
    {
        if(parent == nullptr)
        {
            assert(false);
            return;
        }
        QLineEdit const* const object_parameters_line_edit = parent -> findChild<QLineEdit*>("object_parameters");

        if(object_parameters_line_edit == nullptr)
        {
            assert(false);
            return;
        }
        QStringList const parameters_string_list = object_parameters_line_edit->text().split(";", Qt::SkipEmptyParts);
        int const order = _inputs.get_order();
        std::vector<double> object_parameters {};
        object_parameters.reserve(order + 1);

        std::size_t idx = 1;
        for(auto const& parameter : parameters_string_list)
        {
            object_parameters.push_back(parameter.toDouble());
            if(idx == order + 1)
            {
                break;
            }
            idx++;
        }
        _inputs.set_object_parameters(object_parameters);
    }

    void
    set_controller_parameters(QWidget* parent)
    {
        if(parent == nullptr)
        {
            assert(false);
            return;
        }
        QLineEdit const* const controller_parameters_line_edit = parent -> findChild<QLineEdit*>("controller_parameters");

        if(controller_parameters_line_edit == nullptr)
        {
            assert(false);
            return;
        }
        QStringList const parameters_string_list = controller_parameters_line_edit->text().split(";", Qt::SkipEmptyParts);
        std::size_t const parameters_number = 3u;
        std::vector<double> controller_parameters {};
        controller_parameters.reserve(parameters_number);

        std::size_t idx = 1;
        for(auto const& parameter : parameters_string_list)
        {
            controller_parameters.push_back(parameter.toDouble());
            if(idx == parameters_number)
            {
                break;
            }
            idx++;
        }
        _inputs.set_controller_parameters(controller_parameters);
    }

    void
    set_simulation_parameters(QWidget* parent)
    {
        if(parent == nullptr)
        {
            assert(false);
            return;
        }
        QLineEdit const* const simulation_time_line_edit = parent -> findChild<QLineEdit*>("simulation_time");
        QLineEdit const* const simulation_timestep_line_edit = parent -> findChild<QLineEdit*>("simulation_step");

        if(simulation_time_line_edit == nullptr || simulation_timestep_line_edit == nullptr)
        {
            assert(false);
            return;
        }
        _inputs.set_simulation_time(simulation_time_line_edit->text().toDouble());
        _inputs.set_simulation_time_step(simulation_timestep_line_edit->text().toDouble());
    }

    Input_Parameters_Container const&
    get_input_parameters() const
    {
        return _inputs;
    }
private:
    Input_Parameters_Container _inputs {};
};