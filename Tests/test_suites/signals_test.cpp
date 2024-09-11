// Author: Filip Dymczyk
// Description : Unit tests for signals.

#include <gtest/gtest.h>
#include "signals/signals.h"
#include "test_with_plot.h"

class SignalsTest : public testing::Test, public TestWithPlot
{
    double const _time_step = 0.001;
    Heaviside heaviside {_time_step};
    Ramp ramp {_time_step};
    Rectangle rect {_time_step, 3.0};
    SineWave sine_wave {_time_step, 1.0, 1.0};
protected:
    SignalsTest() : TestWithPlot(15.0) {}

    void
    test_heaviside(std::string signal_plot_title)
    {
        test_signal(&heaviside, signal_plot_title);
    }

    void
    test_ramp(std::string signal_plot_title)
    {
        test_signal(&ramp, signal_plot_title);
    }

    void
    test_rect(std::string signal_plot_title)
    {
        test_signal(&rect, signal_plot_title);
    }

    void
    test_sine_wave(std::string signal_plot_title)
    {
        test_signal(&sine_wave, signal_plot_title);
    }
};

TEST_F(SignalsTest, HeavisideTest)
{
    test_heaviside("Heaviside signal");
}

TEST_F(SignalsTest, RampTest)
{
    test_ramp("Ramp signal");
}

TEST_F(SignalsTest, RectangleTest)
{
    test_rect("Rectangle signal");
}

TEST_F(SignalsTest, SineWaveTest)
{
    test_sine_wave("Sinusoidal signal");
}