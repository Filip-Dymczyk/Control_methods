// Author: Filip Dymczyk
// Description : Multi-order linear object represented by state space.

#pragma once
#include <algorithm>
#include "algebra.h"
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
        VectorT const& C, double D = 0.0)
        : Object_Representation_Base(time_step, order, std::vector<double>(init_state.rbegin(), init_state.rend()))
    {
        assert(A.size() == order);
        assert(A[0].size() == order);
        assert(B.size() == order);
        assert(C.size() == order);
        _matrices = {A, B, C, D};
    }

    Object_State_Space_Representation(double time_step, std::size_t order)
        : Object_State_Space_Representation(
              time_step, order, VectorT(order), MatrixT(order, VectorT(order)), VectorT(order), VectorT(order))
    {
    }

    void
    update(double control) override
    {
        VectorT const current_state = get_current_state();

        set_value_with_measurement_noise(vectors_multiplication_scalar_product<VectorT>(_matrices.C, current_state));

        VectorT A_x(order());
        matrix_vector_multiplication_vector_product<MatrixT, VectorT>(A_x, _matrices.A, current_state);
        VectorT B_u = _matrices.B;
        scale_vector<VectorT>(B_u, control);
        VectorT new_state_derivative(order());
        add_vectors<VectorT>(new_state_derivative, A_x, B_u);
        _state.update(new_state_derivative);
    }

    void
    set_parameters(State_Space_Matrices const& matrices) override
    {
        assert(matrices.A.size() == _order);
        assert(matrices.A[0].size() == _order);
        assert(matrices.B.size() == _order);
        assert(matrices.C.size() == _order);

        _matrices = matrices;
    }

    void
    set_initial_conditions(std::vector<double> initial_conditions) override
    {
        std::reverse(initial_conditions.begin(), initial_conditions.end());
        _state.set_initial_conditions(initial_conditions);
    }

private:
    State_Space_Matrices _matrices;

    VectorT
    get_current_state() const
    {
        VectorT current_state {};
        current_state.reserve(order());

        for(std::size_t i = 0; i < order(); i++)
        {
            current_state.push_back(_state.get_value(i));
        }
        return current_state;
    }
};