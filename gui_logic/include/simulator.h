// Author : Filip Dymczyk
// Description : Simulator class connects Control class to Plotter class.

#pragma once

#include <QtWidgets/QApplication>
#include "control.h"
#include "input_parameters_container.h"
#include "plotter.h"

class Simulator : public QObject
{
    Q_OBJECT

public:
    Simulator(QWidget* parent);

    void
    update(Input_Parameters_Container const& input_parameters);

    void
    run();

    void
    break_simulation();

Q_SIGNALS:
    void
    update_pid_parameters_line_edit_after_tuning(std::array<double, 3> pid_parameters);

private:
    void
    reset();

    bool m_stop_simulation {false};
    bool m_break_simulation {false};
    double m_simulation_time {};
    Control m_control {};
    Plotter* m_plotter {nullptr};

private Q_SLOTS:

    void
    toggle_stop_simulation();
};