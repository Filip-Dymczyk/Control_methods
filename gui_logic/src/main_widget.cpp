#include "main_widget.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

Main_Widget::Main_Widget(QWidget* parent) : QWidget(parent), m_dependency_handler(new Dependency_Handler(this))
{
    connect(m_dependency_handler, &Dependency_Handler::too_many_input_parameters, [this]() {
        QMessageBox::warning(this, "Warning", "Too many input parameters!\nLeaving only the necessary ones.");
    });

    connect(m_dependency_handler, &Dependency_Handler::too_few_input_parameters, [this]() {
        QMessageBox::warning(this, "Warning", "Too few input parameters!\nFilling rest with zeroes.");
    });

    connect(m_dependency_handler, &Dependency_Handler::unable_to_parse, [this](QString text) {
        QMessageBox::warning(this, "Warning", QString("Inserted values: %1 are not allowed!").arg(text));
    });

    connect(m_dependency_handler, &Dependency_Handler::value_below_lower_limit, [this](double limit) {
        QMessageBox::warning(this, "Warning", QString("Inserted value below the limit: %1.").arg(limit));
    });

    connect(m_dependency_handler, &Dependency_Handler::value_above_upper_limit, [this](double limit) {
        QMessageBox::warning(this, "Warning", QString("Inserted value above the limit: %1.").arg(limit));
    });

    connect(
        this, &Main_Widget::plot_control_signal_changed, m_dependency_handler,
        &Dependency_Handler::plot_control_signal_changed);

    connect(
        this, &Main_Widget::enable_measurement_noise, m_dependency_handler,
        &Dependency_Handler::enable_measurement_noise);

    connect(
        this, &Main_Widget::enable_pid_derivative_filtering, m_dependency_handler,
        &Dependency_Handler::enable_pid_derivative_filtering);

    connect(
        m_dependency_handler, &Dependency_Handler::controller_type_changed, this,
        &Main_Widget::controller_type_changed);

    connect(m_dependency_handler, &Dependency_Handler::input_signal_changed, this, &Main_Widget::input_signal_changed);

    QGroupBox* dynamical_system_group_box       = create_dynamical_system_group_box();
    QGroupBox* control_loop_group_box           = create_control_loop_group_box();
    QGroupBox* input_signal_group_box           = create_input_signal_group_box();
    QGroupBox* application_parameters_group_box = create_application_parameters_group_box();

    connect(
        m_control_mode_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
        &Main_Widget::check_tuning_enabled);

    connect(
        m_controller_type_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
        &Main_Widget::check_tuning_enabled);

    QHBoxLayout* horizontal_layout = new QHBoxLayout();
    horizontal_layout->addWidget(dynamical_system_group_box);
    horizontal_layout->addWidget(control_loop_group_box);
    horizontal_layout->addWidget(input_signal_group_box);
    horizontal_layout->addWidget(application_parameters_group_box);

    this->setLayout(horizontal_layout);
}

void
Main_Widget::set_up_line_edit(ClickableLineEdit* line_edit, QString text, QString tooltip, bool preset_id)
{
    line_edit->setText(text);
    line_edit->setToolTip(tooltip);
    if(preset_id)
    {
        line_edit->setProperty("id", static_cast<int>(LineEdit_ID::SIMULATION_TIME_LINE_EDIT));
    }
    else
    {
        line_edit->setProperty("id", m_line_edit_id);
        m_line_edit_id++;
    }

    connect(line_edit, &ClickableLineEdit::clicked, [line_edit]() { line_edit->setFocus(); });
    connect(line_edit, &QLineEdit::editingFinished, m_dependency_handler, &Dependency_Handler::line_edits_callback);
}

void
Main_Widget::set_line_edit_id(int m_line_edit_id_in)
{
    m_line_edit_id = m_line_edit_id_in;
}

bool
Main_Widget::is_tuning_enabled() const
{
    assert((m_control_mode_combobox != nullptr) && (m_controller_type_combobox != nullptr));
    return (static_cast<Control_Mode>(m_control_mode_combobox->currentIndex()) == Control_Mode::CLOSED_LOOP) &&
           (static_cast<Controller_Type>(m_controller_type_combobox->currentIndex()) == Controller_Type::PID);
}

Dependency_Handler const* const
Main_Widget::dependency_handler() const
{
    return m_dependency_handler;
}

void
Main_Widget::update_pid_parameters_line_edit(std::array<double, 3> pid_parameters)
{
    set_controller_parameters_line_edit_text(std::vector<double>(pid_parameters.begin(), pid_parameters.end()));
}

QGroupBox*
Main_Widget::create_dynamical_system_group_box()
{
    QComboBox* object_representation_combobox = new QComboBox();
    {
        std::vector<QString> items;
        items.push_back("Object equation representation");
        items.push_back("Object state space representation");

        set_up_combobox(object_representation_combobox, items);
    }

    connect(
        object_representation_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
        &Main_Widget::update_dynamical_system_layout);

    ClickableLineEdit* initial_conditions_line_edit = new ClickableLineEdit();
    set_up_line_edit(
        initial_conditions_line_edit, "[0.0, 0.0]", "<p><i>Enter initial conditions, e.g [x01, x02].</i></p>");

    ClickableLineEdit* object_parameters_line_edit = new ClickableLineEdit();
    set_up_line_edit(
        object_parameters_line_edit, "[1.0, 1.0]", "<p><i>Enter object parameters as a vector, e.g. [a, b].</i></p>");

    ClickableLineEdit* control_signal_scaler_line_edit = new ClickableLineEdit();
    set_up_line_edit(control_signal_scaler_line_edit, "1.0", "<p><i>Enter control signal scaler.</i></p>");

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

    m_dynamical_system_layout = new QGridLayout();

    int row = 0;
    m_dynamical_system_layout->addWidget(new QLabel("Object representation: "), row, 0);
    m_dynamical_system_layout->addWidget(object_representation_combobox, row, 1);
    row++;
    m_dynamical_system_layout->addWidget(new QLabel("Initial conditions: "), row, 0);
    m_dynamical_system_layout->addWidget(initial_conditions_line_edit, row, 1);
    row++;
    m_dynamical_system_layout->addWidget(new QLabel("Object parameters: "), row, 0);
    m_dynamical_system_layout->addWidget(object_parameters_line_edit, row, 1);
    row++;
    m_dynamical_system_layout->addWidget(new QLabel("Input signal scaler: "), row, 0);
    m_dynamical_system_layout->addWidget(control_signal_scaler_line_edit, row, 1);
    row++;
    m_dynamical_system_layout->addWidget(A_matrix_label, row, 0);
    m_dynamical_system_layout->addWidget(A_matrix_line_edit, row, 1);
    row++;
    m_dynamical_system_layout->addWidget(B_vector_label, row, 0);
    m_dynamical_system_layout->addWidget(B_vector_line_edit, row, 1);
    row++;
    m_dynamical_system_layout->addWidget(C_vector_label, row, 0);
    m_dynamical_system_layout->addWidget(C_vector_line_edit, row, 1);
    row++;
    m_dynamical_system_layout->addWidget(D_label, row, 0);
    m_dynamical_system_layout->addWidget(D_line_edit, row, 1);
    row++;

    QGroupBox* dynamical_system_group_box = new QGroupBox("Dynamical system parameters");
    dynamical_system_group_box->setLayout(m_dynamical_system_layout);

    return dynamical_system_group_box;
}

QGroupBox*
Main_Widget::create_control_loop_group_box()
{
    m_control_mode_combobox = new QComboBox();
    {
        std::vector<QString> items;
        items.push_back("Open loop");
        items.push_back("Closed loop");
        set_up_combobox(m_control_mode_combobox, items);
    }

    m_controller_type_combobox = new QComboBox();
    {
        std::vector<QString> items;
        items.push_back("No controller");
        items.push_back("Bang-Bang controller");
        items.push_back("PID");
        set_up_combobox(m_controller_type_combobox, items);
    }

    m_controller_parameters_line_edit = new ClickableLineEdit();
    set_up_line_edit(
        m_controller_parameters_line_edit, "[0.0, 0.0, 0.0]", "<p><i>Enter controller parameters as a vector.</i></p>");

    m_controller_parameters_line_edit->setEnabled(false);  // No controller as initial controller type.
    connect(m_dependency_handler, &Dependency_Handler::disable_controller_parameters, [this]() {
        m_controller_parameters_line_edit->setEnabled(false);
    });
    connect(m_dependency_handler, &Dependency_Handler::enable_controller_parameters, [this]() {
        m_controller_parameters_line_edit->setEnabled(true);
    });

    QGridLayout* grid_Layout = new QGridLayout();

    int row = 0;
    grid_Layout->addWidget(new QLabel("Control mode: "), row, 0);
    grid_Layout->addWidget(m_control_mode_combobox, row, 1);
    row++;
    grid_Layout->addWidget(new QLabel("Controller type: "), row, 0);
    grid_Layout->addWidget(m_controller_type_combobox, row, 1);
    row++;
    grid_Layout->addWidget(new QLabel("Controller parameters: "), row, 0);
    grid_Layout->addWidget(m_controller_parameters_line_edit, row, 1);

    QGroupBox* control_loop_group_box = new QGroupBox("Control loop parameters");
    control_loop_group_box->setLayout(grid_Layout);

    return control_loop_group_box;
}

QGroupBox*
Main_Widget::create_input_signal_group_box()
{
    QComboBox* input_signal_combobox = new QComboBox();
    {
        std::vector<QString> items;
        items.push_back("No Signal");
        items.push_back("Heaviside");
        items.push_back("Ramp");
        items.push_back("Rectangle");
        items.push_back("Sine wave");
        items.push_back("Pulse wave");
        set_up_combobox(input_signal_combobox, items);
    }
    connect(
        input_signal_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
        &Main_Widget::update_input_signal_layout);

    QGroupBox* input_signal_group_box = new QGroupBox("Input signal parameters");
    m_input_signal_layout             = input_signal_group_box_layout(input_signal_combobox);
    input_signal_group_box->setLayout(m_input_signal_layout);

    return input_signal_group_box;
}

QGroupBox*
Main_Widget::create_application_parameters_group_box()
{
    QComboBox* operation_combobox = new QComboBox();
    {
        std::vector<QString> items;
        items.push_back("Simulation");
        items.push_back("PID Tuning");
        set_up_combobox(operation_combobox, items);
    }
    operation_combobox->setToolTip("Simulate / Tune PID \nTuning available when PID and Closed Loop selected");
    operation_combobox->setEnabled(false);

    auto const lambda = [this, operation_combobox]() {
        bool const enable_tuning = this->is_tuning_enabled();
        operation_combobox->setEnabled(enable_tuning);

        if(!enable_tuning)
        {
            operation_combobox->setCurrentIndex(static_cast<int>(Operation_Type::SIMULATION));
        }
    };

    connect(m_control_mode_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), lambda);
    connect(m_controller_type_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), lambda);

    ClickableLineEdit* simulation_time_line_edit = new ClickableLineEdit(this);
    set_up_line_edit(simulation_time_line_edit, "10.0", "<p><i>Enter operation time in seconds.</i></p>", true);

    QComboBox* simulation_step_combobox = new QComboBox();
    {
        std::vector<QString> items;
        items.push_back("0.01");
        items.push_back("0.001");
        items.push_back("0.0001");
        set_up_combobox(simulation_step_combobox, items, true);
    }

    QGridLayout* grid_Layout = new QGridLayout();

    int row = 0;
    grid_Layout->addWidget(new QLabel("Application configuration: "), row, 0);
    grid_Layout->addWidget(operation_combobox, row, 1);
    row++;
    grid_Layout->addWidget(new QLabel("Operation time [s]: "), row, 0);
    grid_Layout->addWidget(simulation_time_line_edit, row, 1);
    row++;
    grid_Layout->addWidget(new QLabel("Operation time step [s]: "), row, 0);
    grid_Layout->addWidget(simulation_step_combobox, row, 1);

    QGroupBox* application_parameters_group_box = new QGroupBox("Application parameters");
    application_parameters_group_box->setLayout(grid_Layout);

    return application_parameters_group_box;
}

QGridLayout*
Main_Widget::input_signal_group_box_layout(QComboBox* input_signal_combobox)
{
    QLabel* start_time_label = new QLabel("Start time [s]: ");
    start_time_label->hide();

    QLabel* scaler_label = new QLabel("Scaler: ");
    scaler_label->hide();

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

    m_line_edit_id = static_cast<int>(LineEdit_ID::START_TIME_LINE_EDIT);

    m_start_time_line_edit = new ClickableLineEdit();
    set_up_line_edit(m_start_time_line_edit, "0.0", "<p><i>Set up start time in seconds.</i></p>");
    m_start_time_line_edit->hide();

    m_scaler_line_edit = new ClickableLineEdit();
    set_up_line_edit(m_scaler_line_edit, "1.0", "<p><i>Set up scaler parameter.</i></p>");
    m_scaler_line_edit->hide();

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

    int row = 0;
    grid_Layout->addWidget(new QLabel("Input signal type: "), row, 0);
    grid_Layout->addWidget(input_signal_combobox, row, 1);
    row++;
    grid_Layout->addWidget(start_time_label, row, 0);
    grid_Layout->addWidget(m_start_time_line_edit, row, 1);
    row++;
    grid_Layout->addWidget(scaler_label, row, 0);
    grid_Layout->addWidget(m_scaler_line_edit, row, 1);
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
Main_Widget::set_up_combobox(QComboBox* combobox, std::vector<QString> const& option_list, bool numeric)
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

    combobox->setProperty("id", m_combobox_id);
    m_combobox_id++;
    connect(
        combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), m_dependency_handler,
        &Dependency_Handler::comboboxes_callback);
}

void
Main_Widget::hide_show_grid_layout_widgets(
    QGridLayout* grid_layout, int beginning_row, int rows_to_hide_show, bool hide)
{
    for(int row = beginning_row; (row < grid_layout->rowCount()) && (row < beginning_row + rows_to_hide_show); row++)
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

void
Main_Widget::update_input_signal_layout()
{
    QComboBox* combobox = qobject_cast<QComboBox*>(sender());
    assert(combobox != nullptr);

    static constexpr int starting_row = 1;
    hide_show_grid_layout_widgets(m_input_signal_layout, starting_row, m_input_signal_layout->rowCount(), true);

    static constexpr int number_of_basic_signal_parameters = 2;
    static constexpr int rect_starting_row                 = 3;
    static constexpr int sine_wave_starting_row            = 4;
    static constexpr int pulse_wave_starting_row           = 6;
    static constexpr int rect_rows                         = 1;
    static constexpr int sine_wave_rows                    = 2;
    static constexpr int pulse_wave_rows                   = 2;

    Input_Signal const signal_type = static_cast<Input_Signal>(combobox->currentIndex());
    if(signal_type != Input_Signal::NO_SIGNAL)
    {
        hide_show_grid_layout_widgets(m_input_signal_layout, starting_row, number_of_basic_signal_parameters, false);
    }

    switch(signal_type)
    {
        case Input_Signal::RECTANGLE:
            hide_show_grid_layout_widgets(m_input_signal_layout, rect_starting_row, rect_rows, false);
            break;
        case Input_Signal::SINE_WAVE:
            hide_show_grid_layout_widgets(m_input_signal_layout, sine_wave_starting_row, sine_wave_rows, false);
            break;
        case Input_Signal::PULSE_WAVE:
            hide_show_grid_layout_widgets(m_input_signal_layout, pulse_wave_starting_row, pulse_wave_rows, false);
            break;
        default:
            break;
    }
}

void
Main_Widget::update_dynamical_system_layout()
{
    QComboBox* combobox = qobject_cast<QComboBox*>(sender());
    assert(combobox != nullptr);

    static constexpr int equation_beginning_row    = 2;
    static constexpr int equation_layout_rows      = 2;
    static constexpr int state_space_beginning_row = 4;
    static constexpr int state_space_layout_rows   = 4;
    switch(m_previous_object_representation)
    {
        case Object_Representation::EQUATION:
        {
            hide_show_grid_layout_widgets(
                m_dynamical_system_layout, equation_beginning_row, equation_layout_rows, true);
            hide_show_grid_layout_widgets(
                m_dynamical_system_layout, state_space_beginning_row, state_space_layout_rows, false);
            break;
        }
        case Object_Representation::STATE_SPACE:
        {
            hide_show_grid_layout_widgets(
                m_dynamical_system_layout, state_space_beginning_row, state_space_layout_rows, true);
            hide_show_grid_layout_widgets(
                m_dynamical_system_layout, equation_beginning_row, equation_layout_rows, false);
            break;
        }
        default:
        {
            break;
        }
    }

    m_previous_object_representation = static_cast<Object_Representation>(combobox->currentIndex());
}

void
Main_Widget::controller_type_changed(std::vector<double> const& controller_parameters)
{
    set_controller_parameters_line_edit_text(controller_parameters);
}

void
Main_Widget::input_signal_changed(Signal_Base::Signal_Basic_Parameters const& signal_basic_parameters)
{
    m_start_time_line_edit->setText(QString::number(signal_basic_parameters.start_time, 'f', 1));
    m_scaler_line_edit->setText(QString::number(signal_basic_parameters.scaler, 'f', 1));
    Q_EMIT m_start_time_line_edit->editingFinished();
    Q_EMIT m_scaler_line_edit->editingFinished();
}

void
Main_Widget::set_controller_parameters_line_edit_text(std::vector<double> const& controller_parameters)
{
    QString text {};
    QStringList text_list {};
    QTextStream(&text) << "[" << controller_parameters[0] << ", " << controller_parameters[1] << ", "
                       << controller_parameters[2] << "]";

    m_controller_parameters_line_edit->setText(text);
    Q_EMIT m_controller_parameters_line_edit->editingFinished();
}