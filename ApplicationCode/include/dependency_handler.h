// Author : Filip Dymczyk
// Description : Class handling dependencies between application widgets and simulator.

#pragma once
#include <QtCore/QVariant>
#include <QtWidgets/QPushButton>
#include "inputs_parser.h"

class Dependency_Handler : public QObject
{
    Q_OBJECT

public:
    Input_Parameters_Container const&
    get_input_parameters() const
    {
        return _inputs_parser.get_input_parameters();
    }

private:
    Inputs_Parser _inputs_parser {};

public Q_SLOTS:

    void
    order_spinbox_callback(int order)
    {
        _inputs_parser.set_order(order);
    }

    void
    buttons_clicked_callback()
    {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        if(button != nullptr)
        {
            QVariant button_id_variant = button->property("id");
            Button_ID const button_id  = button_id_variant.value<Button_ID>();
            QWidget* parent            = button->parentWidget();

            if(parent == nullptr)
            {
                assert(false);
                return;
            }
            _inputs_parser.parse_button_id(button_id, parent);
        }
    }

    void
    comboboxes_callback()
    {
        QComboBox* combobox = qobject_cast<QComboBox*>(sender());
        if(combobox != nullptr)
        {
            QVariant combobox_id_variant  = combobox->property("id");
            ComboBox_ID const combobox_id = combobox_id_variant.value<ComboBox_ID>();
            int const current_index       = combobox->currentIndex();

            _inputs_parser.parse_combobox_id(combobox_id, current_index);
        }
    }

    void
    simulation_time_step_callback()
    {
        QComboBox* combobox = qobject_cast<QComboBox*>(sender());
        if(combobox != nullptr)
        {
            QVariant const simulation_time_step = combobox->currentData();
            _inputs_parser.set_simulation_time_step(simulation_time_step.toDouble());
        }
    }

Q_SIGNALS:
    void
    show_plot_window();
};