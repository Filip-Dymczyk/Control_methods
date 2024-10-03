// Author : Filip Dymczyk
// Description : Enums definitions.

#pragma once
#include <cstdint>

enum class Button_ID : std::uint8_t
{
    ORDER_BUTTON,
    OBJECT_PARAMETERS_BUTTON,
    CONTROLLER_PARAMETERS_BUTTON,
    RUN_BUTTON
};

enum class Combo_Box_ID : std::uint8_t
{
    OBJECT_REPRESENTATION,
    CONTROL_MODE,
    CONTROLLER_TYPE,
    INPUT_SIGNAL,
    OPERATION_TYPE
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
    NONE,
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