// Author : Filip Dymczyk 
// Description : Class running the application GUI.

#pragma once

#include <QtWidgets/QApplication>

#include "main_window.h"

class Application
{
public:
    static int 
    exec(int argc, char **argv)
    {
        QApplication app(argc, argv);
        MainWindow main_window {};
        main_window.show();
        return app.exec();
    }
};