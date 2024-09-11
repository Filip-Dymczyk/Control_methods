## Repository Overview
The aim of this repository is to increase the knowledge about dynamical systems and control methods as well as - OOP programming skills. It uses c++17 to implement the logic of dynamical systems itself. On top of that, external library - matplotlibcpp is used to display the time reponses of the created simulation objects. Components are tested using Googletest testing framewok.

### Features added:
- Integrator and derivative component.
- Linear SISO object representation based on physical model - single differential equation with primitive state variables dependencies.
- PID controller.
- Open and closed loop control with PID controller.
- Possibility to plot responses using Matplotlibcpp.
- Test API using plots.
- Basic signals: Heaviside, ramp, rectangle, sine wave.
- Vectors and matrices algebra operations.
- Recursive linear regression.
- PID tuning using RLS.
- Testing managed via Googletest.

### Features to be added:
- Other control methods.
- State space model represantation.
- GUI for easier usage of the app.
