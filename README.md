## Author : Filip Dymczyk

## Project aim was to:
- practice *C++17* skills as well as *OOP*, *design patterns* and *best practices*,
- increase knowledge about the behavior of *dynamical control systems* through their logic implementation,
- learn to validate components with the use of *GoogleTest* framework,
- incorporate responses visualization through *Matplotlibcpp*,
- design a GUI using the *Qt* library and connect it to the dynamical systems simulation.

## Logic features:
- support of two representations of dynamical objects: 
    - **differential equation** (SISO), e.g. $\dot{x}$ = $-a_1 x + a_2 u$,
    - **state space** (MIMO): $$\dot{x} = Ax + Bu \\
                            y = Cx + Du $$
- support of two controller types:
    - **PID** - with possible derivative input low pass filtering,
    - **Bang-Bang**.
- possibility of simulating **measurement noise** on the object output,
- ability to create whole control loops, configured as **open** or **closed** ones with or without controllers with a selected object representation,
- different supported input signal types, such as:
    - **Heaviside**,
    - **Ramp**,
    - **Rectangle**,
    - **Sine Wave**,
    - **Pulse Wave**.
- additionally, an experimental feature of **PID Tuner** using **Recursive Linear Regression** was introduced (requires further validation).

#### There are plans to expand the control logic features with:
- different integration (solvers) methods - for now only the simplest **forward Euler** method is utilized,
- support of **discretization** of continuous objects and simulating their behavior taking the sampling time into account,
- other types of controllers, e.g. **LQR**,
- introducing of **observers** and/or **estimators**, such as Kalman filter,
- **output** or **full state** feedback,
- **pole-placing** functionalities, e.g. root-locus, regular pole-placement or using optimization (LQ problem).

## GUI features:
- option to select object representation and entering parameters/matrices in Matlab-like syntax,
- possibility to simulate it's response on the previously mentioned input signal types with an ability to change their parameters,
- option to create more advanced control loops (open/closed) with a selected controller type (with changeable parameters),
- possibility to plot control signal value (optional), simulate measurement noise with a tunable standard deviation and low pass filter the PID derivative input with desired coefficient,
- ability to specify operation time and time step.

#### GUI features to add:
- introduce PID tuning into GUI (for now, it can be selected but has no effect).