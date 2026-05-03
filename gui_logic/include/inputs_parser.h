// Author : Filip Dymczyk
// Description : Class handling inputs parsing.

#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include "input_parameters_container.h"

class Inputs_Parser : public QObject
{
    Q_OBJECT

public:
    Inputs_Parser(QObject* parent = nullptr) : QObject(parent) {}

    void
    parse_line_edit_id(QLineEdit* line_edit, LineEdit_ID line_edit_id);

    void
    parse_combobox_id(QComboBox* combobox, ComboBox_ID combo_box_id);

    std::vector<double>
    parse_vector_parameters(
        QLineEdit* line_edit, int parameters_count = -1, bool parsing_matrix = false, QString splitter = ",");

    std::vector<std::vector<double>>
    parse_matrix_parameters(QLineEdit* line_edit);

    double
    parse_single_number_line_edit(
        QLineEdit* line_edit, double lower_limit = 0.0, double upper_limit = std::numeric_limits<double>::max());

    void
    set_plot_control_signal(bool checked);

    void
    set_enable_measurement_noise(bool checked);

    void
    set_enable_pid_derivative_filtering(bool checked);

    Input_Parameters_Container const&
    get_input_parameters() const;

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

    void
    controller_type_changed(std::vector<double> const& controller_parameters);

    void
    input_signal_changed(Signal_Base::Signal_Basic_Parameters const& signal_basic_parameters);

private:
    Input_Parameters_Container m_inputs {};

    void
    check_disable_enable_controller_parameters(Controller_Type const& new_controller_type);

    QString
    get_new_line_edit_text_from_parameters(std::vector<double> const& parameters);
};