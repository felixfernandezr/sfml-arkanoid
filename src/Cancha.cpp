#include "Cancha.h"
#include <iostream>

Cancha::Cancha()
{
    this->alto = 24;
    this->ancho = 59;
}

void Cancha::delinear()
{
    for(unsigned int i = 0; i < ancho + 2; i++)
        std::cout << '#';
    std::cout << std::endl;

    for(unsigned int i = 0; i < alto; i++)
    {
        std::cout << '#';
        for(unsigned int j = 0; j < ancho; j++)
        {
            std::cout << ' ';
        }
        std::cout << '#' << std::endl;
    }

    for(unsigned int i = 0; i < ancho + 2; i++)
        std::cout << '#';
}
