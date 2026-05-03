#include "object_state_space_representation.h"
#include <algorithm>
#include "algebra.h"

Object_State_Space_Representation::Object_State_Space_Representation(
    double time_step, std::size_t order, VectorT const& init_state, MatrixT const& A, VectorT const& B,
    VectorT const& C, double D)
    : Object_Representation_Base(time_step, order, init_state)
{
    assert(A.size() == order);
    assert(A[0].size() == order);
    assert(B.size() == order);
    assert(C.size() == order);
    m_matrices = {.A = A, .B = B, .C = C, .D = D};
}

Object_State_Space_Representation::Object_State_Space_Representation(double time_step, std::size_t order)
    : Object_State_Space_Representation(
          time_step, order, VectorT(order), MatrixT(order, VectorT(order)), VectorT(order), VectorT(order))
{
}

void
Object_State_Space_Representation::update(double control)
{
    VectorT const current_state = get_current_state();

    set_value_with_measurement_noise(vectors_multiplication_scalar_product(m_matrices.C, current_state));

    VectorT A_x(order());
    matrix_vector_multiplication_vector_product(A_x, m_matrices.A, current_state);
    VectorT B_u = m_matrices.B;
    scale_vector(B_u, control);
    VectorT new_state_derivative(order());
    add_vectors(new_state_derivative, A_x, B_u);
    m_state.update(new_state_derivative);
}

void
Object_State_Space_Representation::set_parameters(State_Space_Matrices const& matrices)
{
    assert(matrices.A.size() == m_order);
    assert(matrices.A[0].size() == m_order);
    assert(matrices.B.size() == m_order);
    assert(matrices.C.size() == m_order);

    m_matrices = matrices;
}

void
Object_State_Space_Representation::set_initial_conditions(std::vector<double> initial_conditions)
{
    std::reverse(initial_conditions.begin(), initial_conditions.end());
    m_state.set_initial_conditions(initial_conditions);
}

Object_State_Space_Representation::VectorT
Object_State_Space_Representation::get_current_state() const
{
    VectorT current_state {};
    current_state.reserve(order());

    for(std::size_t i = 0; i < order(); i++)
    {
        current_state.push_back(m_state.get_value(i));
    }
    return current_state;
}
