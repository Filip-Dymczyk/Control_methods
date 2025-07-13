// Author : Filip Dymczyk
// Description : Plotter class.

#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QString>
#include <QtWidgets/QMainWindow>
#include <vector>
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
        : _chart(new QChart()), _chart_view(new QChartView(_chart)), _chart_window(new QMainWindow(parent))
    {
        _chart->legend()->setVisible(true);

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
        _min_y = std::min(_min_y, std::min(set_point, output));
        _max_y = std::max(_max_y, std::max(set_point, output));

        if(_plot_control_signal)
        {
            _min_y = std::min(_min_y, control);
            _max_y = std::max(_max_y, control);
        }

        _line_series.update(time, set_point, control, output);
    }

    void
    plot(Control_System::Control_Mode control_mode, double time_range)
    {
        _chart_window->hide();

        if(_plot_control_signal && !_chart->series().contains(_line_series.control))
        {
            _chart->addSeries(_line_series.control);
        }
        else if(!_plot_control_signal && _chart->series().contains(_line_series.control))
        {
            _chart->removeSeries(_line_series.control);
        }

        _chart->createDefaultAxes();

        double const y_padding = (_max_y - _min_y) * 0.1;

        _chart->axes(Qt::Horizontal).first()->setRange(0.0, time_range);
        _chart->axes(Qt::Vertical).first()->setRange(_min_y - y_padding, _max_y + y_padding);

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
