// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "components/integrator.h"
#include "components/derivative.h"
#include "math.h"
int main()
{
    double const dt = 0.5f;
    std::size_t count = 10;

    Integrator integ(dt);
    Derivative d(dt);
    double t = 0;

    for(std::size_t i = 0; i < count; i++)
    {
        std::cout << "Integrator value: " << integ.get_value() << std::endl;
        std::cout << "Derivative value: " << d.get_value() << std::endl;
        double const input = sin(2 * 3.14 * t);
        integ.update(input);
        d.update(input);
        t += dt;
    }
    return 0;
}