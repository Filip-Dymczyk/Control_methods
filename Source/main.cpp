// Control methods for linear SISO  dynamical systems.
// Author: Filip Dymczyk

#include "math.h"
#include "sim_objects/integrator.h"
#include "sim_objects/derivative.h"
#include "sim_objects/object.h"
#include "sim_objects/pid.h"
#include "sim_objects/control_system.h"
#include "matplotlibcpp/matplotlibcpp.h"
namespace plt = matplotlibcpp;

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
    Object::coeffs coeffs = {1.0, 1.0, 1.0};
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

void test_open_loop(double const dt, std::size_t const count)
{
    ObjectStandardRepresentation<double, 2> object {dt, {1.0, 1.0, 1.0}, {0.0, 0.0}};
    PID pid {dt, {1.0, 1.0, 0.0}};
    ControlSystem<ObjectStandardRepresentation<double, 2>, PID> control_loop {object, pid, ControlMode::OPEN_LOOP};
    double t = 0;
    for(std::size_t i = 0; i < count; i++)
    {
        double set_point = 0;
        if(t > 1.0)
        {
            set_point = 1.0;
        }
        std::cout << "Output: " << control_loop.get_output() << " at time: "<< t << std::endl;
        control_loop.update(set_point);
        t += dt;
    }
}

void closed_open_loop(double const dt, std::size_t const count)
{
    ObjectStandardRepresentation<double, 2> object {dt, {1.0, -1.0, 1.0}, {0.0, 0.0}};
    PID pid {dt, {6.0, 0.0, 0.0}};
    ControlSystem<ObjectStandardRepresentation<double, 2>, PID> control_loop {object, pid, ControlMode::CLOSED_LOOP};
    double t = 0;
    for(std::size_t i = 0; i < count; i++)
    {
        double set_point = 0;
        if(t > 1.0)
        {
            set_point = 1.0;
        }
        std::cout << "Output: " << control_loop.get_output() << " at time: "<< t << std::endl;
        control_loop.update(set_point);
        t += dt;
    }
}

int main()
{
    plt::plot({1, 2, 3, 4}, "*");
    plt::show();
    return 0;
}