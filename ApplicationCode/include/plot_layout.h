// Author : Filip Dymczyk 
// Description : Plot window layout.

#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

#include "simulator.h"

class PlotLayout : public QVBoxLayout
{
public:
    PlotLayout(QWidget * parent) : QVBoxLayout(parent) {}
private:
    Simulator _simulator {};
};
