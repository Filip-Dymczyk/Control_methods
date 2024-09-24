## Author : Filip Dymczyk.

## Repository overview
The aim of this repository is to increase the knowledge about dynamical systems and control methods, as well as, OOP programming skills. It uses c++17 for implementation. On top of that, it uses: Matplotlibcpp - to display the time reponses of the created simulation objects and GoogleTest - to test the projects elements.

### Features added:
- Integrator and derivative component.
- Linear SISO object representation based on physical model - single differential equation with primitive state variables dependencies.
- PID controller.
- Open and closed loop control with PID controller.
- Possibility to plot responses using Matplotlibcpp.
- Test API using plots.
- Basic signals: Heaviside, ramp, rectangle, sine wave, pulse wave.
- Vectors and matrices algebra operations.
- Recursive linear regression implementation.
- PID tuning using RLS.
- Testing managed via Googletest.
- Two-position (Bang-Bang) controller.
- State space representation for linear SISO object.
- Introduced GUI using Qt framework.

### Features to be added:
- Create simulator class handling whole application logic.
- Incorporate simulator into GUI - create widgets connections and operate control systems based on their states.