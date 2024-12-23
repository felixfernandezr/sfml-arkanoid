#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include "Dupla.h"

class Utils
{
    public:
        static void sleepSegundos(unsigned int segundos);
        static void cuentaRegresivaRecursi(unsigned int inicio, sf::RenderWindow& ventana);
};

#endif // UTILS_H_INCLUDED
