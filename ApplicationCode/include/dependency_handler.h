// Author : Filip Dymczyk
// Description : Class handling dependencies between application widgets and simulator.

#pragma once
#include <iostream>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>

class DependencyHandler : public QObject
{
    Q_OBJECT

enum class Button_ID : std::uint32_t
{
    ORDER_BUTTON,
    OBJECT_PARAMETERS_BUTTON,
    CONTROLLER_PARAMETERS_BUTTON,
    RUN_BUTTON
};

enum class Combo_Box_ID : std::uint32_t
{
    OBJECT_REPRESENTATION,
    CONTROL_MODE,
    CONTROLLER_TYPE,
    INPUT_SIGNAL,
    OPERATION_TYPE
};

public slots:
    void
    buttons_clicked_callback()
    {
        QPushButton * button = qobject_cast<QPushButton*>(sender());
        if (button) 
        {
            QVariant button_id_variant = button -> property("id");
            Button_ID const button_id = button_id_variant.value<Button_ID>();

            switch (button_id)
            {
                case Button_ID::ORDER_BUTTON:
                {
                    break;
                }
                case Button_ID::OBJECT_PARAMETERS_BUTTON:
                {
                    break;
                }
                case Button_ID::CONTROLLER_PARAMETERS_BUTTON:
                {
                    break;
                }
                case Button_ID::RUN_BUTTON:
                {
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    void
    combo_boxes_callback()
    {
        QComboBox * combo_box = qobject_cast<QComboBox*>(sender());
        if (combo_box) 
        {
            QVariant combo_box_id_variant = combo_box -> property("id");
            Combo_Box_ID const combo_box_id = combo_box_id_variant.value<Combo_Box_ID>();
            
            switch (combo_box_id)
            {
                case Combo_Box_ID::OBJECT_REPRESENTATION:
                {
                    break;
                }
                case Combo_Box_ID::CONTROL_MODE:
                {
                    break;
                }
                case Combo_Box_ID::CONTROLLER_TYPE:
                {
                    break;
                }
                case Combo_Box_ID::INPUT_SIGNAL:
                {
                    break;
                }
                case Combo_Box_ID::OPERATION_TYPE:
                {
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
};