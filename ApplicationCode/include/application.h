// Author : Filip Dymczyk
// Description : Class running the application GUI.

#pragma once

#include <QtWidgets/QApplication>
#include "main_window.h"

class Application
{
public:
    static int
    exec(int argc, char** argv)
    {
        QApplication app(argc, argv);
        Main_Window* main_window = new Main_Window();
        main_window->show();  // First show so that the view is set up for centralizing.
        main_window->centralize();
        return app.exec();
    }
};