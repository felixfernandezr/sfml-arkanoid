#ifndef DUPLA_H_INCLUDED
#define DUPLA_H_INCLUDED

#include <stdexcept>
template <class T>
class Dupla {
public:
    T x;
    T y;

    // Constructor
    Dupla(T x = T{}, T y = T{}) : x(x), y(y) {}

    // Overload operator[] to access x or y
    T& operator[](unsigned int i) {
        if (i == 0) {
            return x; // Return reference to x
        } else if (i == 1) {
            return y; // Return reference to y
        } else {
            throw std::out_of_range("Index out of bounds for Dupla");
        }
    }
};

#endif // DUPLA_H_INCLUDED
