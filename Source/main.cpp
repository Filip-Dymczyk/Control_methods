// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "math.h"
#include "sim_objects/integrator.h"
#include "sim_objects/derivative.h"
#include "sim_objects/object.h"
#include "sim_objects/pid.h"

void test_components(double const dt, std::size_t const count)
{
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
}

void test_object(double const dt, std::size_t const count)
{
    using Object = ObjectStandardRepresentation<double, 2>;
    Object::coeffs coeffs = {-1.0, -1.0, 1.0};
    Object::initial_state init_state = {0.0, 0.0};
    Object second_order_object(dt, coeffs, init_state);

    double t = 0;
    for(std::size_t i = 0; i < count; i++)
    {
        double input = 0;
        if(t > 1.0)
        {
            input = 1.0;
        }
        std::cout << "Output: " << second_order_object.x() << " at time: "<< t << std::endl;
        second_order_object.update(input);
        t += dt;
    }
}

void test_pid(double const dt, std::size_t const count)
{
    PID pid {dt, {1.0, 1.0, 0.0}};

    double t = 0;
    for(std::size_t i = 0; i < count; i++)
    {
        double input = 0;
        if(t >= 1.0)
        {
            input = 1.0;
        }
        std::cout << "Output: " << pid.get_value() << " at time: "<< t << std::endl;
        pid.update(input);
        t += dt;
    }
}

int main()
{
    double const dt = 0.01f;
    std::size_t const count = 300;
    test_pid(dt, count);
    return 0;
}