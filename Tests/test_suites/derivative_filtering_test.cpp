// Author: Filip Dymczyk
// Description : Unit test for derivative filtering.

#include <gtest/gtest.h>
#include "derivative.h"
#include "signals.h"
#include "test_with_plot.h"

class DerivativeFilteringTest : public testing::Test, public Test_With_Plot
{
    static constexpr double _time_step    = 0.1;

protected:
    DerivativeFilteringTest() : Test_With_Plot(4.0) {}

    void
    test_derivative()
    {
        Test_With_Plot::test_component(&_derivative, &_pulse_wave);
         _derivative.reset();
        _pulse_wave.reset();
    }

protected:
    Derivative _derivative {_time_step};
    Pulse_Wave _pulse_wave {_time_step, 0.5, 2.0, {}};
};

TEST_F(DerivativeFilteringTest, DerivativeFilteringTest) 
{ 
    test_derivative();

    _derivative.set_filtering_coefficient(0.8);
    _derivative.enable_filtering(true);

    test_derivative();

    _derivative.enable_filtering(false);

    test_derivative();

    _derivative.enable_filtering(true);

    test_derivative();
}