#include "dependency_handler.h"
#include <QtWidgets/QComboBox>

Dependency_Handler::Dependency_Handler(QObject* parent) : QObject(parent), m_inputs_parser(new Inputs_Parser(this))
{
    connect(
        m_inputs_parser, &Inputs_Parser::disable_controller_parameters, this,
        &Dependency_Handler::disable_controller_parameters);
    connect(
        m_inputs_parser, &Inputs_Parser::enable_controller_parameters, this,
        &Dependency_Handler::enable_controller_parameters);

    connect(
        m_inputs_parser, &Inputs_Parser::too_many_input_parameters, this,
        &Dependency_Handler::too_many_input_parameters);
    connect(
        m_inputs_parser, &Inputs_Parser::too_few_input_parameters, this, &Dependency_Handler::too_few_input_parameters);

    connect(m_inputs_parser, &Inputs_Parser::unable_to_parse, this, &Dependency_Handler::unable_to_parse);
    connect(
        m_inputs_parser, &Inputs_Parser::value_below_lower_limit, this, &Dependency_Handler::value_below_lower_limit);
    connect(
        m_inputs_parser, &Inputs_Parser::value_above_upper_limit, this, &Dependency_Handler::value_above_upper_limit);

    connect(
        m_inputs_parser, &Inputs_Parser::controller_type_changed, this, &Dependency_Handler::controller_type_changed);
    connect(m_inputs_parser, &Inputs_Parser::input_signal_changed, this, &Dependency_Handler::input_signal_changed);
}

Input_Parameters_Container const&
Dependency_Handler::get_input_parameters() const
{
    return m_inputs_parser->get_input_parameters();
}

void
Dependency_Handler::line_edits_callback()
{
    QLineEdit* line_edit = qobject_cast<QLineEdit*>(sender());
    assert(line_edit != nullptr);

    line_edit->clearFocus();

    QVariant line_edit_id_variant  = line_edit->property("id");
    LineEdit_ID const line_edit_id = line_edit_id_variant.value<LineEdit_ID>();

    m_inputs_parser->parse_line_edit_id(line_edit, line_edit_id);
}

void
Dependency_Handler::comboboxes_callback()
{
    QComboBox* combobox = qobject_cast<QComboBox*>(sender());
    assert(combobox != nullptr);

    QVariant combobox_id_variant  = combobox->property("id");
    ComboBox_ID const combobox_id = combobox_id_variant.value<ComboBox_ID>();

    m_inputs_parser->parse_combobox_id(combobox, combobox_id);
}

void
Dependency_Handler::plot_control_signal_changed(bool checked)
{
    m_inputs_parser->set_plot_control_signal(checked);
}

void
Dependency_Handler::enable_measurement_noise(bool checked)
{
    m_inputs_parser->set_enable_measurement_noise(checked);
}

void
Dependency_Handler::enable_pid_derivative_filtering(bool checked)
{
    m_inputs_parser->set_enable_pid_derivative_filtering(checked);
}