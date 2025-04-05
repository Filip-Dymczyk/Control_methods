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
#include "clickable_line_edit.h"
#include "dependency_handler.h"
#include "enums.h"

class Main_Widget : public QWidget
{
    Q_OBJECT

public:
    Main_Widget(QWidget* parent) : QWidget(parent), _dependency_handler(new Dependency_Handler())
    {
        connect(_dependency_handler, &Dependency_Handler::too_many_input_parameters, [this]() {
            QMessageBox::warning(this, "Warning", "Too many input parameters!\nLeaving only the necessary ones.");
        });
        connect(_dependency_handler, &Dependency_Handler::too_few_input_parameters, [this]() {
            QMessageBox::warning(this, "Warning", "Too few input parameters!\nFilling rest with zeroes.");
        });

        QGroupBox* dynamical_system_group_box = create_dynamical_system_group_box();
        QGroupBox* control_loop_group_box     = create_control_loop_group_box();
        QGroupBox* input_signal_group_box =
            create_input_signal_group_box(Input_Signal::HEAVISIDE);  // Default signal type.
        QGroupBox* application_parameters_group_box = create_application_parameters_group_box();

        QHBoxLayout* horizontal_layout = new QHBoxLayout();
        horizontal_layout->addWidget(dynamical_system_group_box);
        horizontal_layout->addWidget(control_loop_group_box);
        horizontal_layout->addWidget(input_signal_group_box);
        horizontal_layout->addWidget(application_parameters_group_box);

        this->setLayout(horizontal_layout);
    }

    Dependency_Handler const* const
    dependency_handler() const
    {
        return _dependency_handler;
    }

private:
    int combobox_id  = 0;
    int line_edit_id = 0;
    Dependency_Handler* _dependency_handler {nullptr};

    QGroupBox*
    create_dynamical_system_group_box()
    {
        QSpinBox* order_spin_box = new QSpinBox();
        order_spin_box->setRange(1, 10);
        order_spin_box->setValue(1);
        connect(
            order_spin_box, QOverload<int>::of(&QSpinBox::valueChanged), _dependency_handler,
            &Dependency_Handler::order_spinbox_callback);

        QComboBox* object_representation_combobox = new QComboBox();
        set_up_combobox(
            object_representation_combobox, {"Object equation representation", "Object state space representation"});

        ClickableLineEdit* object_parameters_line_edit = new ClickableLineEdit();
        set_up_line_edit(
            object_parameters_line_edit, "1.0|1.0",
            "<p><i>Enter object parameters separated by pipes (|).</i></p>"
            "<p><b>NOTE!</b> Format accepted:</p>"
            "<p><code>ax' + bx = cu</code></p>");

        QGridLayout* grid_Layout = new QGridLayout();

        int row = 0;
        grid_Layout->addWidget(new QLabel("Object order: "), row, 0);
        grid_Layout->addWidget(order_spin_box, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Object representation: "), row, 0);
        grid_Layout->addWidget(object_representation_combobox, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Object parameters: "), row, 0);
        grid_Layout->addWidget(object_parameters_line_edit, row, 1);

        QGroupBox* dynamical_system_group_box = new QGroupBox("Dynamical system parameters");
        dynamical_system_group_box->setLayout(grid_Layout);

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
            controller_parameters_line_edit, "1.0|1.0|0.0",
            "<p><i>Enter controller parameters divided with pipe (|).</i></p>"
            "<p><b>NOTE!</b> Only first 3 parameters will be accepted.</p>");

        controller_parameters_line_edit->setEnabled(false);  // No controller as initial controller type.
        connect(
            _dependency_handler, &Dependency_Handler::disable_controller_parameters,
            [controller_parameters_line_edit]() { controller_parameters_line_edit->setEnabled(false); });
        connect(
            _dependency_handler, &Dependency_Handler::enable_controller_parameters,
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
    create_input_signal_group_box(Input_Signal option)
    {
        QComboBox* input_signal_combobox = new QComboBox();
        set_up_combobox(input_signal_combobox, {"Heaviside", "Ramp", "Rectangle", "Sine wave", "Pulse wave"});
        input_signal_combobox->setCurrentIndex(static_cast<int>(option));

        QGroupBox* input_signal_group_box = new QGroupBox("Input signal parameters");
        // Case will be done for the Input Signal.
        input_signal_group_box->setLayout(basic_signal_layout(input_signal_combobox));

        return input_signal_group_box;
    }

    QGroupBox*
    create_application_parameters_group_box()
    {
        QComboBox* operation_combobox = new QComboBox();
        set_up_combobox(operation_combobox, {"Simulation", "Tuning"});

        ClickableLineEdit* simulation_time_line_edit = new ClickableLineEdit();
        set_up_line_edit(simulation_time_line_edit, "1.0", "<p><i>Enter operation time in seconds.</i></p>", true);

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
            combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), _dependency_handler,
            &Dependency_Handler::comboboxes_callback);
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
        connect(line_edit, &QLineEdit::editingFinished, _dependency_handler, &Dependency_Handler::line_edits_callback);
    }

    QGridLayout*
    basic_signal_layout(QComboBox* input_signal_combobox)
    {
        line_edit_id = static_cast<int>(LineEdit_ID::START_TIME_LINE_EDIT);

        ClickableLineEdit* start_time_line_edit = new ClickableLineEdit();
        set_up_line_edit(start_time_line_edit, "0.0", "<p><i>Set up start time in seconds.</i></p>");

        ClickableLineEdit* scaler_line_edit = new ClickableLineEdit();
        set_up_line_edit(scaler_line_edit, "1.0", "<p><i>Set up scaler parameter.</i></p>");

        QGridLayout* grid_Layout = new QGridLayout();

        int row = 0;
        grid_Layout->addWidget(new QLabel("Input signal type: "), row, 0);
        grid_Layout->addWidget(input_signal_combobox, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Start time [s]: "), row, 0);
        grid_Layout->addWidget(start_time_line_edit, row, 1);
        row++;
        grid_Layout->addWidget(new QLabel("Scaler: "), row, 0);
        grid_Layout->addWidget(scaler_line_edit, row, 1);

        return grid_Layout;
    }
};