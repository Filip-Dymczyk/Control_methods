// Author : Filip Dymczyk
// Description : Class handling dependencies between application widgets and simulator.

#pragma once
#include <iostream>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtWidgets/QPushButton>

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
public slots:
    void
    connect_confirm_order_button()
    {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
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
};