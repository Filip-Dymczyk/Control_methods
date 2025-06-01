// Author : Filip Dymczyk
// Description : Enums definitions.

#pragma once
#include <cstdint>

enum class LineEdit_ID : std::uint8_t
{
    OBJECT_PARAMETERS_LINE_EDIT,
    A_MATRIX_LINE_EDIT,
    B_VECTOR_LINE_EDIT,
    C_VECTOR_LINE_EDIT,
    D_LINE_EDIT,
    CONTROLLER_PARAMETERS_LINE_EDIT,
    START_TIME_LINE_EDIT,
    SCALER_LINE_EDIT,
    ON_TIME_LINE_EDIT,
    OMEGA_LINE_EDIT,
    OFFSET_LINE_EDIT,
    PERIOD_LINE_EDIT,
    DUTY_CYCLE_LINE_EDIT,
    SIMULATION_TIME_LINE_EDIT,
    MEASUREMENT_NOISE_LINE_EDIT
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

enum class Advanced_Input_Signal_Parameters : std::uint8_t
{
    ON_TIME,
    OMEGA,
    OFFSET,
    PERIOD,
    DUTY_CYCLE
};