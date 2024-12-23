#include "Niveles.h"
#include <iostream>

// This class contain game levels "raw" templates
// This templates are then randomized in Obstaculos obstaculos.inicializarObstaculos()

Niveles::Niveles() {}

std::vector<std::vector<unsigned int>> Niveles::nivel1() // All functions returning actual template vector
{
    this->plantilla.resize(2, std::vector<unsigned int>(15));

    this->plantilla = {
        {1, 1},
        {1, 1}
    };
    /*{0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1}*/
    return this->plantilla;
}

std::vector<std::vector<unsigned int>> Niveles::nivel2()
{
    this->plantilla.resize(3, std::vector<unsigned int>(15));

    this->plantilla = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    /*{0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}*/
    return this->plantilla;
}

std::vector<std::vector<unsigned int>> Niveles::nivel3()
{
    this->plantilla.resize(4, std::vector<unsigned int>(15));

    this->plantilla = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    /*{0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}*/
    return this->plantilla;
}
