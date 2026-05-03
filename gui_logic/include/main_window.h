// Author : Filip Dymczyk
// Description : Main application window.

#pragma once

#include <QtWidgets/QMainWindow>
#include <tuple>
#include "main_widget.h"
#include "simulator.h"

class Main_Window : public QMainWindow
{
    Q_OBJECT

    QString const window_title = "Dynamical systems control methods.";

public:
    Main_Window();

    void
    centralize();

private:
    std::tuple<int, int> m_center_position {};
    Main_Widget* m_main_widget {nullptr};
    Simulator* m_simulator {nullptr};

    void
    run_simulation();

    void
    center();

    QToolBar*
    create_toolbar();

    void
    closeEvent(QCloseEvent* event) override;
};