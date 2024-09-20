// Author: Filip Dymczyk
// Description : Multi-order linear object represented by state space.

#pragma once
#include <random>
#include "sim_object_base.h"
#include "state.h"

// NOTE: SISO object represented via state space:
//              x' = Ax + Bu
//              y  = Cx + Du
// where: n - number of state variables,
// A is [n x n] matrix, B is [n x 1] vector, C is [1 x n] transposed vector D is a scalar (by default set to 0).
// We allow entering whole matrices / vectors with coefficients.
// When entering coeficients beware of mistakingly creating unstable objects!
// We allow to set up desired initial conditions in a manner: {x'(0), x(0)}.
// Object already simulates measurement white noises (output).
template<std::size_t order>
class ObjectStateSpaceRepresentation : public SimumlationObjectBase
{   
public:
    using MatrixT = std::array<std::array<double, order>, order>;
    using VectorT = std::array<double, order>;

    ObjectStateSpaceRepresentation(double time_step, MatrixT const & A, VectorT const & B, VectorT const & C, double D = 0.0, initial_state const & init_state) : SimumlationObjectBase(time_step), _state(time_step, init_state), _A(A), _B(B), _C(C), _D(D) {}

    void 
    update(double control) override
    {
    }

    std::size_t
    get_order() const
    {
        return _order;
    }
private:
    std::size_t const _order = order;
    State<order> _state;
    MatrixT _A {};
    VectorT _B {};
    VectorT _C {};
    double _D {};

    std::mt19937 generator;
    std::normal_distribution<double> distribution {0.0, 0.1};

    double
    measurement_noise()
    {
        return distribution(generator);
    }
};