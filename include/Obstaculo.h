#ifndef OBSTACULO_H_INCLUDED
#define OBSTACULO_H_INCLUDED
#include <SFML/Graphics.hpp>

#include <vector>
#include "Niveles.h"

class Obstaculo
{
    private:
        float ancho; // Width of each obstacle
        std::vector<std::vector<unsigned int>> grilla; // Grid for obstacle strength
        std::vector<std::vector<sf::RectangleShape>> obstaculos; // SFML shapes for obstacles
        unsigned int filas; // Number of rows
        unsigned int columnas; // Number of columns

    public:
        Obstaculo(unsigned int ancho);
        void inicializarObstaculos(const std::vector<std::vector<unsigned int>>& nivel); // Initialize obstacles
        bool checkColision(float pelotaX, float pelotaY); // Check ball collision
        void dibujar(sf::RenderWindow& ventana); // Draw obstacles
        bool checkNivelCompleto(); // Check if level is complete
        unsigned int getNumeroAleatorio(unsigned int a, unsigned int b);
};

#endif // OBSTACULO_H_INCLUDED
