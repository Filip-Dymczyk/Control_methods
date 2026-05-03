// Author: Filip Dymczyk
// Description : Multi-order linear object represented by state space.

#pragma once
#include "base_classes/object_representation_base.h"

// NOTE: SISO object represented via state space:
//              x' = Ax + Bu
//              y  = Cx + Du
// where: n - number of state variables,
// A is [n x n] matrix, B is [n x 1] vector, C is [1 x n] transposed vector D is a scalar (by default set to 0).
// We allow entering whole matrices / vectors with coefficients.
// When entering coefficients beware of mistakenly creating unstable objects!
// We allow to set up desired initial conditions in a manner: {x'(0), x(0)}.
// Object already simulates measurement white noises (output).
class Object_State_Space_Representation : public Object_Representation_Base
{
    using MatrixT = std::vector<std::vector<double>>;
    using VectorT = std::vector<double>;

public:
    Object_State_Space_Representation(
        double time_step, std::size_t order, VectorT const& init_state, MatrixT const& A, VectorT const& B,
        VectorT const& C, double D = 0.0);

    Object_State_Space_Representation(double time_step, std::size_t order);

    void
    update(double control) override;

    void
    set_parameters(State_Space_Matrices const& matrices) override;

    void
    set_initial_conditions(std::vector<double> initial_conditions) override;

private:
    State_Space_Matrices m_matrices;

    VectorT
    get_current_state() const;
};