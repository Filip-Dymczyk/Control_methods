#include "plotter.h"

Plotter::Plotter(QWidget* parent)
    : QObject(parent),
      m_line_series(this),
      m_axis_x(new QValueAxis()),
      m_axis_y(new QValueAxis()),
      m_chart(new QChart()),
      m_chart_view(new QChartView(m_chart)),
      m_chart_window(new QMainWindow(dynamic_cast<QWidget*>(this)))
{
    m_axis_x->setTitleText("Time [s]");
    m_axis_y->setTitleText("Output");

    m_chart->legend()->setVisible(true);
    m_chart->addAxis(m_axis_x, Qt::AlignBottom);
    m_chart->addAxis(m_axis_y, Qt::AlignLeft);

    m_chart_view->setRenderHint(QPainter::Antialiasing);
    m_chart_view->setRubberBand(QChartView::RectangleRubberBand);
    m_chart_view->setDragMode(QGraphicsView::NoDrag);

    m_chart_window->resize(800, 600);
    m_chart_window->setWindowTitle("Plot");

    QWidget* central_widget = new QWidget();
    QVBoxLayout* layout     = new QVBoxLayout();
    layout->addWidget(m_chart_view);
    central_widget->setLayout(layout);

    m_chart->addSeries(m_line_series.set_point);
    m_chart->addSeries(m_line_series.output);

    m_line_series.set_point->attachAxis(m_axis_x);
    m_line_series.set_point->attachAxis(m_axis_y);
    m_line_series.output->attachAxis(m_axis_x);
    m_line_series.output->attachAxis(m_axis_y);

    m_chart_window->setCentralWidget(central_widget);

    QPushButton* reset_zoom_button = new QPushButton("Reset Zoom");
    QObject::connect(reset_zoom_button, &QPushButton::clicked, [this]() { m_chart->zoomReset(); });

    m_stop_simulation_button = new QPushButton("Stop simulation");
    m_stop_simulation_button->setCheckable(true);
    connect(m_stop_simulation_button, &QPushButton::toggled, this, &Plotter::toggle_stop_simulation);

    QToolBar* toolbar = new QToolBar();
    toolbar->addWidget(reset_zoom_button);
    toolbar->addWidget(m_stop_simulation_button);

    m_chart_window->addToolBar(toolbar);
}

void
Plotter::set_plot_control_signal(bool plot_control_signal)
{
    m_plot_control_signal = plot_control_signal;
}

void
Plotter::update(double time, double set_point, double control, double output)
{
    static double const abs_diff = 0.01;
    double new_min               = m_min_y;
    double new_max               = m_max_y;
    new_min                      = std::min(new_min, std::min(set_point, output));
    new_max                      = std::max(new_max, std::max(set_point, output));

    if(m_plot_control_signal)
    {
        new_min = std::min(new_min, control);
        new_max = std::max(new_max, control);
    }

    if((std::abs(m_min_y - new_min) >= abs_diff) || (std::abs(m_max_y - new_max) >= abs_diff))
    {
        m_min_y = new_min;
        m_max_y = new_max;

        double const y_padding = (m_max_y - m_min_y) * 0.1;
        m_axis_y->setRange(m_min_y - y_padding, m_max_y + y_padding);
    }
    m_line_series.update(time, set_point, control, output);
}

void
Plotter::show_chart(Control_System::Control_Mode control_mode, double time_range)
{
    if(m_plot_control_signal && !m_chart->series().contains(m_line_series.control))
    {
        m_chart->addSeries(m_line_series.control);
        m_line_series.control->attachAxis(m_axis_x);
        m_line_series.control->attachAxis(m_axis_y);
    }
    else if(!m_plot_control_signal && m_chart->series().contains(m_line_series.control))
    {
        m_line_series.control->detachAxis(m_axis_x);
        m_line_series.control->detachAxis(m_axis_y);
        m_chart->removeSeries(m_line_series.control);
    }

    m_axis_x->setRange(0.0, time_range);
    set_chart_title(control_mode);
    m_chart_window->show();
}

void
Plotter::reset()
{
    m_min_y = std::numeric_limits<double>::infinity();
    m_max_y = -std::numeric_limits<double>::infinity();
    m_line_series.reset();
    m_stop_simulation_button->setChecked(false);
}

bool
Plotter::is_window_open() const
{
    if(m_chart_window == nullptr)
    {
        return false;
    }
    return m_chart_window->isVisible();
}

void
Plotter::set_chart_title(Control_System::Control_Mode control_mode)
{
    QString title {};
    switch(control_mode)
    {
        case Control_System::Control_Mode::CLOSED_LOOP:
            title = "Closed loop control system response";
            break;
        case Control_System::Control_Mode::OPEN_LOOP:
            title = "Open loop control system response";
            break;
        default:
            title = "Component response";
            break;
    }

    m_chart->setTitle(title);
}