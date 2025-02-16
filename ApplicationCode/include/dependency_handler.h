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
    buttons_clicked_callback()
    {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        if(button)
        {
            QVariant button_id_variant = button->property("id");
            Button_ID const button_id  = button_id_variant.value<Button_ID>();
            QWidget* parent            = button->parentWidget();

            if(parent == nullptr)
            {
                assert(false);
                return;
            }
            bool const is_run = _inputs_parser.parse_button_id(button_id, parent);

            if(is_run)
            {
                Q_EMIT show_plot_window();
            }
        }
    }

    void
    combo_boxes_callback()
    {
        QComboBox* combo_box = qobject_cast<QComboBox*>(sender());
        if(combo_box)
        {
            QVariant combo_box_id_variant   = combo_box->property("id");
            Combo_Box_ID const combo_box_id = combo_box_id_variant.value<Combo_Box_ID>();
            int const current_index         = combo_box->currentIndex();

            _inputs_parser.parse_combo_box_id(combo_box_id, current_index);
        }
    }

Q_SIGNALS:
    void
    show_plot_window();
};