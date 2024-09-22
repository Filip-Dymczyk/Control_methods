// Author : Filip Dymczyk 
// Description : Main application window.

#pragma once
#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include "main_layout.h"

class MainWindow : public QWidget
{
    static constexpr unsigned width = 500;
    static constexpr unsigned height = 700;
    const QString window_title = "Dynamical systems control methods.";
public:
    MainWindow() 
    {   
        this -> setWindowTitle(window_title);
        this -> setFixedSize(width, height);
        this -> setLayout(&main_layout);
    }
private:
    MainLayout main_layout {};
};