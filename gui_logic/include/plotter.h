// Author : Filip Dymczyk
// Description : Plotter class.

#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include "control_system.h"

class Plotter : public QObject
{
    Q_OBJECT

    struct LineSeries
    {
        QLineSeries* set_point {nullptr};
        QLineSeries* output {nullptr};
        QLineSeries* control {nullptr};

        LineSeries(QObject* parent)
        {
            set_point = new QLineSeries(parent);
            output    = new QLineSeries(parent);
            control   = new QLineSeries(parent);

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
    Plotter(QWidget* parent);

    void
    set_plot_control_signal(bool plot_control_signal);

    void
    update(double time, double set_point, double control, double output);

    void
    show_chart(Control_System::Control_Mode control_mode, double time_range);

    void
    reset();

    bool
    is_window_open() const;

Q_SIGNALS:
    void
    toggle_stop_simulation();

private:
    bool m_plot_control_signal {false};
    double m_min_y {std::numeric_limits<double>::infinity()};
    double m_max_y {-std::numeric_limits<double>::infinity()};
    LineSeries m_line_series;
    QValueAxis* m_axis_x {nullptr};
    QValueAxis* m_axis_y {nullptr};
    QChart* m_chart {nullptr};
    QChartView* m_chart_view {nullptr};
    QMainWindow* m_chart_window {nullptr};
    QPushButton* m_stop_simulation_button {nullptr};

    void
    set_chart_title(Control_System::Control_Mode control_mode);
};
