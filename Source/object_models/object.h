// Author: Filip Dymczyk
// Description : Base class for multi-order linear objects.

#pragma once
#include <iostream>

template<typename T, std::size_t order>
class ObjectStandardRepresentation
{   
public:
    using coeffs = std::array<T, order + 1>;
    using base_type = T;

    ObjectStandardRepresentation(coeffs coefficients) : _coefficients(coefficients) {}

    std::size_t const
    get_order() const
    {
        return _order;
    }
    
    coeffs const &
    get_coefss() const
    {
        return coeffs;
    }

    coeffs
    get_coeffs() const
    {
        return coeffs;
    }
private:
    std::size_t _order = order;
    coeffs _coefficients {};
};