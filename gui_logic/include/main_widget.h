// Author : Filip Dymczyk
// Description : Main application window layout.

#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include "clickable_line_edit.h"
#include "dependency_handler.h"

class Main_Widget : public QWidget
{
    Q_OBJECT

public:
    Main_Widget(QWidget* parent);

    void
    set_up_line_edit(ClickableLineEdit* line_edit, QString text, QString tooltip, bool preset_id = false);

    void
    set_line_edit_id(int m_line_edit_id_in);

    bool
    is_tuning_enabled() const;

    Dependency_Handler const* const
    dependency_handler() const;

public Q_SLOTS:

    void
    update_pid_parameters_line_edit(std::array<double, 3> pid_parameters);

Q_SIGNALS:
    void
    plot_control_signal_changed(bool checked);

    void
    enable_measurement_noise(bool checked);

    void
    enable_pid_derivative_filtering(bool checked);

    void
    check_tuning_enabled();

private:
    int m_combobox_id  = 0;
    int m_line_edit_id = 0;
    Object_Representation m_previous_object_representation {Object_Representation::EQUATION};
    QGridLayout* m_input_signal_layout {nullptr};
    QGridLayout* m_dynamical_system_layout {nullptr};
    QComboBox* m_control_mode_combobox {nullptr};
    QComboBox* m_controller_type_combobox {nullptr};
    ClickableLineEdit* m_controller_parameters_line_edit {nullptr};
    ClickableLineEdit* m_start_time_line_edit {nullptr};
    ClickableLineEdit* m_scaler_line_edit {nullptr};
    Dependency_Handler* m_dependency_handler {nullptr};

    QGroupBox*
    create_dynamical_system_group_box();

    QGroupBox*
    create_control_loop_group_box();

    QGroupBox*
    create_input_signal_group_box();

    QGroupBox*
    create_application_parameters_group_box();

    QGridLayout*
    input_signal_group_box_layout(QComboBox* input_signal_combobox);

    void
    set_up_combobox(QComboBox* combobox, std::vector<QString> const& option_list, bool numeric = false);

    void
    hide_show_grid_layout_widgets(QGridLayout* grid_layout, int beginning_row, int rows_to_hide_show, bool hide);

private Q_SLOTS:

    void
    update_input_signal_layout();

    void
    update_dynamical_system_layout();

    void
    controller_type_changed(std::vector<double> const& controller_parameters);

    void
    input_signal_changed(Signal_Base::Signal_Basic_Parameters const& signal_basic_parameters);

    void
    set_controller_parameters_line_edit_text(std::vector<double> const& controller_parameters);
};