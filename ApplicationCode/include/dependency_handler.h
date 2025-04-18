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
    Dependency_Handler() : _inputs_parser(new Inputs_Parser())
    {
        connect(
            _inputs_parser, &Inputs_Parser::disable_controller_parameters, this,
            &Dependency_Handler::disable_controller_parameters);
        connect(
            _inputs_parser, &Inputs_Parser::enable_controller_parameters, this,
            &Dependency_Handler::enable_controller_parameters);

        connect(
            _inputs_parser, &Inputs_Parser::too_many_input_parameters, this,
            &Dependency_Handler::too_many_input_parameters);
        connect(
            _inputs_parser, &Inputs_Parser::too_few_input_parameters, this,
            &Dependency_Handler::too_few_input_parameters);

        connect(_inputs_parser, &Inputs_Parser::unable_to_parse, this, &Dependency_Handler::unable_to_parse);
        connect(
            _inputs_parser, &Inputs_Parser::value_below_lower_limit, this,
            &Dependency_Handler::value_below_lower_limit);
        connect(
            _inputs_parser, &Inputs_Parser::value_above_upper_limit, this,
            &Dependency_Handler::value_above_upper_limit);
    }

    Input_Parameters_Container const&
    get_input_parameters() const
    {
        return _inputs_parser->get_input_parameters();
    }

private:
    Inputs_Parser* _inputs_parser {nullptr};

public Q_SLOTS:

    void
    order_spinbox_callback(int order)
    {
        _inputs_parser->set_order(order);
    }

    void
    line_edits_callback()
    {
        QLineEdit* line_edit = qobject_cast<QLineEdit*>(sender());
        if(line_edit != nullptr)
        {
            line_edit->clearFocus();

            QVariant line_edit_id_variant  = line_edit->property("id");
            LineEdit_ID const line_edit_id = line_edit_id_variant.value<LineEdit_ID>();

            _inputs_parser->parse_line_edit_id(line_edit, line_edit_id);
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

            _inputs_parser->parse_combobox_id(combobox, combobox_id);
        }
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
};