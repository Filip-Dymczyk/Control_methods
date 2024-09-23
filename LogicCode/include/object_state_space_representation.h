// Author: Filip Dymczyk
// Description : Multi-order linear object represented by state space.

#pragma once
#include <random>
#include "algebra.h"
#include "object_representation_base.h"

// NOTE: SISO object represented via state space:
//              x' = Ax + Bu
//              y  = Cx + Du
// where: n - number of state variables,
// A is [n x n] matrix, B is [n x 1] vector, C is [1 x n] transposed vector D is a scalar (by default set to 0).
// We allow entering whole matrices / vectors with coefficients.
// When entering coeficients beware of mistakingly creating unstable objects!
// We allow to set up desired initial conditions in a manner: {x'(0), x(0)}.
// Object already simulates measurement white noises (output).
class ObjectStateSpaceRepresentation : public ObjectRepresentationBase
{   
    using MatrixT = std::vector<std::vector<double>>;
    using VectorT = std::vector<double>;
public:
    ObjectStateSpaceRepresentation(double time_step, 
                                std::uint32_t order, 
                                VectorT const & init_state, 
                                MatrixT const & A, 
                                VectorT const & B, 
                                VectorT const & C, 
                                double D = 0.0) : 
                                ObjectRepresentationBase(time_step, order, init_state)
    {
        assert(A.size() == order);
        assert(A[0].size() == order);
        assert(B.size() == order);
        assert(C.size() == order);
        _A = A;
        _B = B;
        _C = C;
        _D = D;
    }

    void 
    update(double control) override
    {
        VectorT const current_state = get_current_state();
        VectorT A_x (order());
        matrix_vector_multiplication_vector_product<MatrixT, VectorT>(A_x, _A, current_state);
        VectorT B_u = _B;
        scale_vector<VectorT>(B_u, control);
        VectorT new_state_derivative (order());
        add_vectors<VectorT>(new_state_derivative, A_x, B_u);
        _state.update(new_state_derivative);
        
        set_value(vectors_multiplication_scalar_product<VectorT>(_C, current_state) + measurement_noise());
    }
private:
    MatrixT _A;
    VectorT _B;
    VectorT _C;
    double _D {};

    VectorT
    get_current_state() const
    {
        VectorT current_state {};
        for(std::size_t i = 0; i < order(); i++)
        {
            current_state.push_back(_state.get_value(i));
        }
        return current_state;
    }
};