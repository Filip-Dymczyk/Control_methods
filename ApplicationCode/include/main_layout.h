// Author : Filip Dymczyk 
// Description : Main application window layout.

#pragma once

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtCore/Qt>

class MainLayout : public QVBoxLayout
{
public:
    MainLayout()
    {
        configure_widgets();
        add_widgets();
        set_alignemnt();
    }
private:
    QLabel select_order_label {};
    QSpinBox order_spin_box {};

    void
    configure_widgets()
    {
        select_order_label.setText("Choose the order of dynamical system");
        order_spin_box.setRange(0, 10);
        order_spin_box.setValue(0);
    }

    void
    add_widgets()
    {
        this -> addWidget(&select_order_label);
        this -> addWidget(&order_spin_box);
    }

    void
    set_alignemnt()
    {
        this -> setAlignment(Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignCenter);
    }
};