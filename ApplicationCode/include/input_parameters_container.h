// Author : Filip Dymczyk
// Description : Dependency handler input parameter container.

#pragma once
#include <cstdint>
#include <vector>
#include "enums.h"

class InputParameterContainer
{
    struct Buttons_Inputs
    {
        bool run_flag {};
        std::uint8_t order {1u};
        std::vector<double> object_parameters {};
        std::vector<double> controller_params {};
    };

    struct Combo_Boxes_Inputs
    {
        Object_Representation object_representation = Object_Representation::EQUATION;
        Control_Mode control_mode = Control_Mode::OPEN_LOOP;
        Controller_Type controller_type = Controller_Type::NONE;
        Input_Signal input_signal = Input_Signal::NONE;
        Operation_Type operation_type = Operation_Type::SIMULATION;
    };
private:
    Buttons_Inputs _button_inputs {};
    Combo_Boxes_Inputs _combo_boxes_inputs {};
};