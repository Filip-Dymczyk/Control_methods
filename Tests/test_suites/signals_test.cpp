// Author: Filip Dymczyk
// Description : Unit tests for signals.

#include <gtest/gtest.h>
#include "signals/signals.h"
#include "test_with_plot.h"

class SignalsTest : public testing::Test, public TestWithPlot
{
    double const time_step = 0.1;
    Heaviside heaviside {time_step};
protected:
    SignalsTest() : TestWithPlot(15.0) {}

    void
    test_heaviside(std::string signal_plot_title)
    {
        test_signal(&heaviside, signal_plot_title);
    }
};

TEST_F(SignalsTest, HeavisideTest)
{
    test_heaviside("Heaviside signal");
}