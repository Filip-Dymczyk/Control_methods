// Author : Filip Dymczyk
// Description : Main application window layout.

#pragma once

#include <QtCore/QObject>
#include <QtCore/Qt>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include <memory>
#include "clickable_line_edit.h"
#include "dependency_handler.h"
#include "enums.h"

class Main_Widget : public QWidget
{
    Q_OBJECT

public:
    Main_Widget(QWidget* parent) : QWidget(parent), _dependency_handler(std::make_unique<Dependency_Handler>())
    {
        connect(_dependency_handler.get(), &Dependency_Handler::too_many_input_parameters, [this]() {
            QMessageBox::warning(this, "Warning", "Too many input parameters!\nLeaving only the necessary ones.");
        });
        connect(_dependency_handler.get(), &Dependency_Handler::too_few_input_parameters, [this]() {
            QMessageBox::warning(this, "Warning", "Too few input parameters!\nFilling rest with zeroes.");
        });

        connect(_dependency_handler.get(), &Dependency_Handler::unable_to_parse, [this](QString text) {
            QMessageBox::warning(this, "Warning", QString("Inserted values: %1 are not allowed!").arg(text));
        });
        connect(_dependency_handler.get(), &Dependency_Handler::value_below_lower_limit, [this](double limit) {
            QMessageBox::warning(this, "Warning", QString("Inserted value below the limit: %1.").arg(limit));
        });
        connect(_dependency_handler.get(), &Dependency_Handler::value_above_upper_limit, [this](double limit) {
            QMessageBox::warning(this, "Warning", QString("Inserted value above the limit: %1.").arg(limit));
        });

        connect(
            this, &Main_Widget::plot_control_signal_changed, _dependency_handler.get(),
            &Dependency_Handler::plot_control_signal_changed);
        connect(
            this, &Main_Widget::enable_measurement_noise, _dependency_handler.get(),
            &Dependency_Handler::enable_measurement_noise);
        connect(
            this, &Main_Widget::enable_pid_derivative_filtering, _dependency_handler.get(),
            &Dependency_Handler::enable_pid_derivative_filtering);

        QGroupBox* dynamical_system_group_box       = create_dynamical_system_group_box();
        QGroupBox* control_loop_group_box           = create_control_loop_group_box();
        QGroupBox* input_signal_group_box           = create_input_signal_group_box();
        QGroupBox* application_parameters_group_box = create_application_parameters_group_box();

        QHBoxLayout* horizontal_layout = new QHBoxLayout();
        horizontal_layout->addWidget(dynamical_system_group_box);
        horizontal_layout->addWidget(control_loop_group_box);
        horizontal_layout->addWidget(input_signal_group_box);
        horizontal_layout->addWidget(application_parameters_group_box);

        this->setLayout(horizontal_layout);
    }

    void
    set_up_line_edit(ClickableLineEdit* line_edit, QString text, QString tooltip, bool preset_id = false)
    {
        line_edit->setText(text);
        line_edit->setToolTip(tooltip);
        if(preset_id)
        {
            line_edit->setProperty("id", static_cast<int>(LineEdit_ID::SIMULATION_TIME_LINE_EDIT));
        }
        else
        {
            line_edit->setProperty("id", line_edit_id);
            line_edit_id++;
        }

        connect(line_edit, &ClickableLineEdit::clicked, [line_edit]() { line_edit->setFocus(); });
        connect(
            line_edit, &QLineEdit::editingFinished, _dependency_handler.get(),
            &Dependency_Handler::line_edits_callback);
    }

    void
    set_line_edit_id(int line_edit_id_in)
    {
        line_edit_id = line_edit_id_in;
    }

    Dependency_Handler const* const
    dependency_handler() const
    {
        return _dependency_handler.get();
    }

Q_SIGNALS:
    void
    plot_control_signal_changed(bool checked);

    void
    enable_measurement_noise(bool checked);

    void
    enable_pid_derivative_filtering(bool checked);

private:
    int combobox_id  = 0;
    int line_edit_id = 0;
    Input_Signal _previous_input_signal_type {Input_Signal::HEAVISIDE};
    Object_Representation _previous_object_representation {Object_Representation::EQUATION};
    QGridLayout* _input_signal_layout {nullptr};
    QGridLayout* _dynamical_system_layout {nullptr};
    std::unique_ptr<Dependency_Handler> _dependency_handler {nullptr};

    QGroupBox*
    create_dynamical_system_group_box()
    {
        QComboBox* object_representation_combobox = new QComboBox();
        set_up_combobox(
            object_representation_combobox, {"Object equation representation", "Object state space representation"});
        connect(
            object_representation_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &update_dynamical_system_layout);

        ClickableLineEdit* initial_conditions_line_edit = new ClickableLineEdit();
        set_up_line_edit(
            initial_conditions_line_edit, "[0.0, 0.0]", "<p><i>Enter initial conditions, e.g [x01, x02].</i></p>");

        ClickableLineEdit* object_parameters_line_edit = new ClickableLineEdit();
        set_up_line_edit(
            object_parameters_line_edit, "[1.0, 1.0, 1.0]",
            "<p><i>Enter object parameters as a vector, e.g. [a, b].</i></p>");

        QLabel* A_matrix_label = new QLabel("A: ");
        A_matrix_label->hide();

        QLabel* B_vector_label = new QLabel("B: ");
        B_vector_label->hide();

        QLabel* C_vector_label = new QLabel("C: ");
        C_vector_label->hide();

        QLabel* D_label = new QLabel("D: ");
        D_label->hide();

        ClickableLineEdit* A_matrix_line_edit = new ClickableLineEdit();
        set_up_line_edit(
            A_matrix_line_edit, "[0.0, 1.0; -1.0, -1.0]", "<p><i>Enter object A matrix, e.g. [a, b; c, d].</i></p>");
        A_matrix_line_edit->hide();

        ClickableLineEdit* B_vector_line_edit = new ClickableLineEdit();
        set_up_line_edit(B_vector_line_edit, "[0.0; 1.0]", "<p><i>Enter object B vector, e.g. [a; b].</i></p>");
        B_vector_line_edit->hide();

        ClickableLineEdit* C_vector_line_edit = new ClickableLineEdit();
        set_up_line_edit(C_vector_line_edit, "[1.0, 0.0]", "<p><i>Enter object C vector, e.g. [a, b].</i></p>");
        C_vector_line_edit->hide();

        ClickableLineEdit* D_line_edit = new ClickableLineEdit();
        set_up_line_edit(D_line_edit, "0.0", "<p><i>Enter object D value.</i></p>");
        D_line_edit->hide();

        _dynamical_system_layout = new QGridLayout();

        int row = 0;
        _dynamical_system_layout->addWidget(new QLabel("Object representation: "), row, 0);
        _dynamical_system_layout->addWidget(object_representation_combobox, row, 1);
        row++;
        _dynamical_system_layout->addWidget(new QLabel("Initial conditions: "), row, 0);
        _dynamical_system_layout->addWidget(initial_conditions_line_edit, row, 1);
        row++;
        _dynamical_system_layout->addWidget(new QLabel("Object parameters: "), row, 0);
        _dynamical_system_layout->addWidget(object_parameters_line_edit, row, 1);
        row++;
        _dynamical_system_layout->addWidget(A_matrix_label, row, 0);
        _dynamical_system_layout->addWidget(A_matrix_line_edit, row, 1);
        row++;
        _dynamical_system_layout->addWidget(B_vector_label, row, 0);
        _dynamical_system_layout->addWidget(B_vector_line_edit, row, 1);
        row++;
        _dynamical_system_layout->addWidget(C_vector_label, row, 0);
        _dynamical_system_layout->addWidget(C_vector_line_edit, row, 1);
        row++;
        _dynamical_system_layout->addWidget(D_label, row, 0);
        _dynamical_system_layout->addWidget(D_line_edit, row, 1);
        row++;

        QGroupBox* dynamical_system_group_box = new QGroupBox("Dynamical system parameters");
        dynamical_system_group_box->setLayout(_dynamical_system_layout);

        return dynamical_system_group_box;
    }

    QGroupBox*
    create_control_loop_group_box()
    {
        QComboBox* control_mode_combobox = new QComboBox();
        set_up_combobox(control_mode_combobox, {"Open loop", "Closed loop"});

        QComboBox* controller_type_combobox = new QComboBox();
        set_up_combobox(controller_type_combobox, {"No controller", "Bang-Bang controller", "PID"});

        ClickableLineEdit* controller_parameters_line_edit = new ClickableLineEdit();
        set_up_line_edit(
            controller_parameters_line_edit, "[1.0, 1.0, 0.0]",
            "<p><i>Enter controller parameters as a vector.</i></p>");

        controller_parameters_line_edit->setEnabled(false);  // No controller as initial controller type.
        connect(
            _dependency_handler.get(), &Dependency_Handler::disable_controller_parameters,
            [controller_parameters_line_edit]() { controller_parameters_line_edit->setEnabled(false); });
        connect(
            _dependency_handler.get(), &Dependency_Handler::enable_controller_parameters,
            [controller_parameters_line_edit]() { controller_parameters_line_edit->setEnabled(true); });

        QGridLayout* grid_Layout = new QGridLayout();

        int row = 0;
        grid_Layout->addWidget(new QLabel("Control mode: "), row, 0);
        grid_Layout->addWidget(control_mode_combobox, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Controller type: "), row, 0);
        grid_Layout->addWidget(controller_type_combobox, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Controller parameters: "), row, 0);
        grid_Layout->addWidget(controller_parameters_line_edit, row, 1);

        QGroupBox* control_loop_group_box = new QGroupBox("Control loop parameters");
        control_loop_group_box->setLayout(grid_Layout);

        return control_loop_group_box;
    }

    QGroupBox*
    create_input_signal_group_box()
    {
        QComboBox* input_signal_combobox = new QComboBox();
        set_up_combobox(input_signal_combobox, {"Heaviside", "Ramp", "Rectangle", "Sine wave", "Pulse wave"});
        connect(
            input_signal_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &update_input_signal_layout);

        QGroupBox* input_signal_group_box = new QGroupBox("Input signal parameters");
        _input_signal_layout              = input_signal_group_box_layout(input_signal_combobox);
        input_signal_group_box->setLayout(_input_signal_layout);

        return input_signal_group_box;
    }

    QGroupBox*
    create_application_parameters_group_box()
    {
        QComboBox* operation_combobox = new QComboBox();
        set_up_combobox(operation_combobox, {"Simulation", "Tuning"});

        ClickableLineEdit* simulation_time_line_edit = new ClickableLineEdit();
        set_up_line_edit(simulation_time_line_edit, "10.0", "<p><i>Enter operation time in seconds.</i></p>", true);

        QComboBox* _simulation_step_combobox = new QComboBox();
        set_up_combobox(_simulation_step_combobox, {"0.01", "0.001", "0.0001"}, true);

        QGridLayout* grid_Layout = new QGridLayout();

        int row = 0;
        grid_Layout->addWidget(new QLabel("Application configuration: "), row, 0);
        grid_Layout->addWidget(operation_combobox, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Operation time [s]: "), row, 0);
        grid_Layout->addWidget(simulation_time_line_edit, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Operation time step [s]: "), row, 0);
        grid_Layout->addWidget(_simulation_step_combobox, row, 1);

        QGroupBox* application_parameters_group_box = new QGroupBox("Application parameters");
        application_parameters_group_box->setLayout(grid_Layout);

        return application_parameters_group_box;
    }

    QGridLayout*
    input_signal_group_box_layout(QComboBox* input_signal_combobox)
    {
        QLabel* on_time_label = new QLabel("On time [s]: ");
        on_time_label->hide();

        QLabel* omega_label = new QLabel("Omega [rad/s]: ");
        omega_label->hide();

        QLabel* offset_label = new QLabel("Offset: ");
        offset_label->hide();

        QLabel* period_label = new QLabel("Period [s]: ");
        period_label->hide();

        QLabel* duty_cycle_label = new QLabel("Duty cycle [%]: ");
        duty_cycle_label->hide();

        line_edit_id = static_cast<int>(LineEdit_ID::START_TIME_LINE_EDIT);

        ClickableLineEdit* start_time_line_edit = new ClickableLineEdit();
        set_up_line_edit(start_time_line_edit, "0.0", "<p><i>Set up start time in seconds.</i></p>");

        ClickableLineEdit* scaler_line_edit = new ClickableLineEdit();
        set_up_line_edit(scaler_line_edit, "1.0", "<p><i>Set up scaler parameter.</i></p>");

        ClickableLineEdit* on_time_line_edit = new ClickableLineEdit();
        set_up_line_edit(on_time_line_edit, "5.0", "<p><i>Set up on time in seconds.</i></p>");
        on_time_line_edit->hide();

        ClickableLineEdit* omega_line_edit = new ClickableLineEdit();
        set_up_line_edit(omega_line_edit, "1.0", "<p><i>Set up omega in radians per second.</i></p>");
        omega_line_edit->hide();

        ClickableLineEdit* offset_line_edit = new ClickableLineEdit();
        set_up_line_edit(offset_line_edit, "0.0", "<p><i>Set up offset.</i></p>");
        offset_line_edit->hide();

        ClickableLineEdit* period_line_edit = new ClickableLineEdit();
        set_up_line_edit(period_line_edit, "2.0", "<p><i>Set up period in seconds.</i></p>");
        period_line_edit->hide();

        ClickableLineEdit* duty_cycle_line_edit = new ClickableLineEdit();
        set_up_line_edit(duty_cycle_line_edit, "50.0", "<p><i>Set up duty cycle 0 - 100%.</i></p>");
        duty_cycle_line_edit->hide();

        QGridLayout* grid_Layout = new QGridLayout();

        // Default widgets (shared among all the input signals) are not hidden.
        int row = 0;
        grid_Layout->addWidget(new QLabel("Input signal type: "), row, 0);
        grid_Layout->addWidget(input_signal_combobox, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Start time [s]: "), row, 0);
        grid_Layout->addWidget(start_time_line_edit, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Scaler: "), row, 0);
        grid_Layout->addWidget(scaler_line_edit, row, 1);
        row++;

        grid_Layout->addWidget(on_time_label, row, 0);
        grid_Layout->addWidget(on_time_line_edit, row, 1);
        row++;
        grid_Layout->addWidget(omega_label, row, 0);
        grid_Layout->addWidget(omega_line_edit, row, 1);
        row++;
        grid_Layout->addWidget(offset_label, row, 0);
        grid_Layout->addWidget(offset_line_edit, row, 1);
        row++;
        grid_Layout->addWidget(period_label, row, 0);
        grid_Layout->addWidget(period_line_edit, row, 1);
        row++;
        grid_Layout->addWidget(duty_cycle_label, row, 0);
        grid_Layout->addWidget(duty_cycle_line_edit, row, 1);

        return grid_Layout;
    }

    void
    set_up_combobox(QComboBox* combobox, QList<QString> const& option_list, bool numeric = false)
    {
        for(QString const& option: option_list)
        {
            if(!numeric)
            {
                combobox->addItem(option);
            }
            else
            {
                combobox->addItem(option, option.toDouble());
            }
        }

        combobox->setProperty("id", combobox_id);
        combobox_id++;

        connect(
            combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), _dependency_handler.get(),
            &Dependency_Handler::comboboxes_callback);
    }

    int
    get_valid_grid_layout_row(Input_Signal signal_type) const
    {
        int valid_row = 0;
        switch(signal_type)
        {
            case Input_Signal::RECTANGLE:
            {
                valid_row = static_cast<int>(signal_type) + 1;
                break;
            }
            case Input_Signal::SINE_WAVE:
            {
                valid_row = static_cast<int>(signal_type) + 1;
                break;
            }
            case Input_Signal::PULSE_WAVE:
            {
                valid_row = static_cast<int>(signal_type) + 2;
                break;
            }
            default:
            {
                break;
            }
        }
        return valid_row;
    }

    void
    hide_show_grid_layout_widgets(QGridLayout* grid_layout, int beginning_row, int rows_to_hide_show, bool hide)
    {
        for(int row = beginning_row; (row < grid_layout->rowCount() && row < beginning_row + rows_to_hide_show); row++)
        {
            for(int column = 0; column < grid_layout->columnCount(); column++)
            {
                QLayoutItem* item = grid_layout->itemAtPosition(row, column);
                if(item != nullptr)
                {
                    QWidget* widget = item->widget();
                    if(widget != nullptr)
                    {
                        if(hide)
                        {
                            widget->hide();
                        }
                        else
                        {
                            widget->show();
                        }
                    }
                }
            }
        }
    }

private Q_SLOTS:

    void
    update_input_signal_layout()
    {
        QComboBox* combobox = qobject_cast<QComboBox*>(sender());
        if(combobox == nullptr)
        {
            return;
        }

        int const previous_signal_type_row = get_valid_grid_layout_row(_previous_input_signal_type);
        switch(_previous_input_signal_type)
        {
            case Input_Signal::RECTANGLE:
            {
                hide_show_grid_layout_widgets(_input_signal_layout, previous_signal_type_row, 1, true);
                break;
            }
            case Input_Signal::SINE_WAVE:
            {
                hide_show_grid_layout_widgets(_input_signal_layout, previous_signal_type_row, 2, true);
                break;
            }
            case Input_Signal::PULSE_WAVE:
            {
                hide_show_grid_layout_widgets(_input_signal_layout, previous_signal_type_row, 2, true);
                break;
            }
            default:
            {
                break;  // Don't hide anything for HEAVISIDE/RAMP input signal as it's just basic layout.
            }
        }

        Input_Signal const signal_type    = static_cast<Input_Signal>(combobox->currentIndex());
        int const current_signal_type_row = get_valid_grid_layout_row(signal_type);
        switch(signal_type)
        {
            case Input_Signal::RECTANGLE:
            {
                hide_show_grid_layout_widgets(_input_signal_layout, current_signal_type_row, 1, false);
                break;
            }
            case Input_Signal::SINE_WAVE:
            {
                hide_show_grid_layout_widgets(_input_signal_layout, current_signal_type_row, 2, false);
                break;
            }
            case Input_Signal::PULSE_WAVE:
            {
                hide_show_grid_layout_widgets(_input_signal_layout, current_signal_type_row, 2, false);
                break;
            }
            default:
            {
                break;  // Don't show anything for HEAVISIDE/RAMP input signal as it's just basic layout.
            }
        }
        _previous_input_signal_type = signal_type;
    }

    void
    update_dynamical_system_layout()
    {
        QComboBox* combobox = qobject_cast<QComboBox*>(sender());
        if(combobox == nullptr)
        {
            return;
        }

        static int const EQUATION_BEGINNING_ROW    = 2;
        static int const EQUATION_LAYOUT_ROWS      = 1;
        static int const STATE_SPACE_BEGINNING_ROW = 3;
        static int const STATE_SPACE_LAYOUT_ROWS   = 4;
        switch(_previous_object_representation)
        {
            case Object_Representation::EQUATION:
            {
                hide_show_grid_layout_widgets(
                    _dynamical_system_layout, EQUATION_BEGINNING_ROW, EQUATION_LAYOUT_ROWS, true);
                hide_show_grid_layout_widgets(
                    _dynamical_system_layout, STATE_SPACE_BEGINNING_ROW, STATE_SPACE_LAYOUT_ROWS, false);
                break;
            }
            case Object_Representation::STATE_SPACE:
            {
                hide_show_grid_layout_widgets(
                    _dynamical_system_layout, STATE_SPACE_BEGINNING_ROW, STATE_SPACE_LAYOUT_ROWS, true);
                hide_show_grid_layout_widgets(
                    _dynamical_system_layout, EQUATION_BEGINNING_ROW, EQUATION_LAYOUT_ROWS, false);
                break;
            }
            default:
            {
                break;
            }
        }

        _previous_object_representation = static_cast<Object_Representation>(combobox->currentIndex());
    }
};