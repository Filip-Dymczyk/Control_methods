#include "derivative.h"
#include <algorithm>

void
Derivative::update(double input)
{
    assert(get_time_step() > 0.0);

    if(m_enable_filtering)
    {
        input = m_filtering_coefficient * m_previous_input + (1.0 - m_filtering_coefficient) * input;
    }

    double const derivative = (input - m_previous_input) / get_time_step();
    set_value(derivative);

    m_previous_input = input;
}

void
Derivative::reset()
{
    set_value(0.0);
    m_previous_input = 0.0;
}

void
Derivative::enable_filtering(bool enable)
{
    m_enable_filtering = enable;
}

void
Derivative::set_filtering_coefficient(double filtering_coefficient)
{
    m_filtering_coefficient = std::clamp(filtering_coefficient, 0.0, 1.0);
}