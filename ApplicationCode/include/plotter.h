// Author : Filip Dymczyk
// Description : Plotter class.

#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "control_system.h"

class Plotter
{
    struct LineSeries
    {
        QLineSeries* set_point {nullptr};
        QLineSeries* output {nullptr};
        QLineSeries* control {nullptr};

        LineSeries()
        {
            set_point = new QLineSeries();
            output    = new QLineSeries();
            control   = new QLineSeries();

            set_point->setName("Set Point");
            set_point->setColor(Qt::red);

            control->setName("Control");
            control->setColor(QColorConstants::Svg::orange);

            output->setName("Output");
            output->setColor(Qt::blue);
        }

        void
        update(double time, double set_point, double control, double output)
        {
            this->set_point->append(time, set_point);
            this->output->append(time, output);
            this->control->append(time, control);
        }

        void
        reset()
        {
            set_point->clear();
            output->clear();
            control->clear();
        }
    };

public:
    Plotter(QWidget* parent)
        : _axis_x(new QValueAxis()),
          _axis_y(new QValueAxis()),
          _chart(new QChart()),
          _chart_view(new QChartView(_chart)),
          _chart_window(new QMainWindow(parent))
    {
        _axis_x->setTitleText("Time [s]");
        _axis_y->setTitleText("Output");

        _chart->legend()->setVisible(true);
        _chart->addAxis(_axis_x, Qt::AlignBottom);
        _chart->addAxis(_axis_y, Qt::AlignLeft);

        _chart_view->setRenderHint(QPainter::Antialiasing);
        _chart_view->setRubberBand(QChartView::RectangleRubberBand);
        _chart_view->setDragMode(QGraphicsView::NoDrag);

        _chart_window->resize(800, 600);
        _chart_window->setWindowTitle("Plot");

        QWidget* central_widget = new QWidget();
        QVBoxLayout* layout     = new QVBoxLayout(central_widget);
        layout->addWidget(_chart_view);

        QPushButton* reset_zoom_button = new QPushButton("Reset Zoom");
        layout->addWidget(reset_zoom_button);

        QObject::connect(reset_zoom_button, &QPushButton::clicked, [this]() { _chart->zoomReset(); });

        _chart->addSeries(_line_series.set_point);
        _chart->addSeries(_line_series.output);

        _line_series.set_point->attachAxis(_axis_x);
        _line_series.set_point->attachAxis(_axis_y);
        _line_series.output->attachAxis(_axis_x);
        _line_series.output->attachAxis(_axis_y);

        _chart_window->setCentralWidget(central_widget);
    }

    void
    set_plot_control_signal(bool plot_control_signal)
    {
        _plot_control_signal = plot_control_signal;
    }

    void
    update(double time, double set_point, double control, double output)
    {
        static double const abs_diff = 0.01;
        double new_min               = _min_y;
        double new_max               = _max_y;
        new_min                      = std::min(new_min, std::min(set_point, output));
        new_max                      = std::max(new_max, std::max(set_point, output));

        if(_plot_control_signal)
        {
            new_min = std::min(new_min, control);
            new_max = std::max(new_max, control);
        }

        if((std::abs(_min_y - new_min) >= abs_diff) || (std::abs(_max_y - new_max) >= abs_diff))
        {
            _min_y = new_min;
            _max_y = new_max;

            double const y_padding = (_max_y - _min_y) * 0.1;
            _chart->axes(Qt::Vertical).first()->setRange(_min_y - y_padding, _max_y + y_padding);
        }
        _line_series.update(time, set_point, control, output);
    }

    void
    show_chart(Control_System::Control_Mode control_mode, double time_range)
    {
        if(_plot_control_signal && !_chart->series().contains(_line_series.control))
        {
            _chart->addSeries(_line_series.control);
            _line_series.control->attachAxis(_axis_x);
            _line_series.control->attachAxis(_axis_y);
        }
        else if(!_plot_control_signal && _chart->series().contains(_line_series.control))
        {
            _line_series.control->detachAxis(_axis_x);
            _line_series.control->detachAxis(_axis_y);
            _chart->removeSeries(_line_series.control);
        }

        _axis_x->setRange(0.0, time_range);
        set_chart_title(control_mode);
        _chart_window->show();
    }

    void
    reset()
    {
        _min_y = std::numeric_limits<double>::infinity();
        _max_y = -std::numeric_limits<double>::infinity();
        _line_series.reset();
    }

private:
    bool _plot_control_signal {false};
    double _min_y {std::numeric_limits<double>::infinity()};
    double _max_y {-std::numeric_limits<double>::infinity()};
    LineSeries _line_series {};
    QValueAxis* _axis_x {nullptr};
    QValueAxis* _axis_y {nullptr};
    QChart* _chart {nullptr};
    QChartView* _chart_view {nullptr};
    QMainWindow* _chart_window {nullptr};

    void
    set_chart_title(Control_System::Control_Mode control_mode)
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

        _chart->setTitle(title);
    }
};
