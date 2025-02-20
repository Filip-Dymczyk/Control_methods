// Author : Filip Dymczyk
// Description : Enums definitions.

#pragma once
#include <cstdint>

enum class LineEdit_ID : std::uint8_t
{
    OBJECT_PARAMETERS_LINE_EDIT,
    CONTROLLER_PARAMETERS_LINE_EDIT,
    SIMULATION_TIME_LINE_EDIT
};

enum class ComboBox_ID : std::uint8_t
{
    OBJECT_REPRESENTATION,
    CONTROL_MODE,
    CONTROLLER_TYPE,
    INPUT_SIGNAL,
    OPERATION_TYPE,
    SIMULATION_TIME_STEP
};

enum class Object_Representation : std::uint8_t
{
    EQUATION,
    STATE_SPACE
};

enum class Control_Mode : std::uint8_t
{
    OPEN_LOOP,
    CLOSED_LOOP
};

enum class Controller_Type : std::uint8_t
{
    NONE,
    BANG_BANG,
    PID
};

enum class Input_Signal : std::uint8_t
{
    HEAVISIDE,
    RAMP,
    RECTANGLE,
    SINE_WAVE,
    PULSE_WAVE
};

enum class Operation_Type : std::uint8_t
{
    SIMULATION,
    TUNING
};