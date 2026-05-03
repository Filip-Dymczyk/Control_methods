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
    Dependency_Handler(QObject* parent);

    Input_Parameters_Container const&
    get_input_parameters() const;

private:
    Inputs_Parser* m_inputs_parser;

public Q_SLOTS:

    void
    line_edits_callback();

    void
    comboboxes_callback();

    void
    plot_control_signal_changed(bool checked);

    void
    enable_measurement_noise(bool checked);

    void
    enable_pid_derivative_filtering(bool checked);

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
};