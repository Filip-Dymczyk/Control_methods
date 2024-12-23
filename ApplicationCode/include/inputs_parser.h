// Author : Filip Dymczyk
// Description : Class handling inputs parsing.

#pragma once
#include <QtCore/QObject>
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
        QSpinBox * order_spin_box = parent -> findChild<QSpinBox *>("order");
        if(order_spin_box == nullptr)
        {
            assert(false);
        }
        std::uint8_t const value = static_cast<uint8_t>(order_spin_box -> value());
        _inputs.set_order(value);
    }

    void
    set_object_parameters(QWidget* parent)
    {
        QLineEdit * object_parameters_line_edit = parent -> findChild<QLineEdit *>("object_parameters");
        if(object_parameters_line_edit == nullptr)
        {
            assert(false);
        }
        // object_parameters_line_edit -> text() // will need parsing
        // _inputs.set_object_parameters();
    }

    void
    set_controller_parameters(QWidget* parent)
    {
        QLineEdit * controller_parameters_line_edit = parent -> findChild<QLineEdit *>("controller_parameters");
        if(controller_parameters_line_edit == nullptr)
        {
            assert(false);
        }
        // object_parameters_line_edit -> text() // will need parsing
        // _inputs.set_controller_parameters();
    }
private:
    InputParameterContainer _inputs {};
};