#ifndef PELOTA_H
#define PELOTA_H
#include <SFML/Graphics.hpp>

#include "Dupla.h"

class Pelota
{
    public:
        sf::CircleShape pelota;
        sf::Vector2f posicion;
        sf::Vector2f direccion;
        float velocidad;

    public:
        Pelota();
        void mover(); // Move the ball
        void reiniciar(); // Reset position and direction
        void rebotarX(); // Bounce in X axis
        void rebotarY(); // Bounce in Y axis
        void dibujar(sf::RenderWindow& ventana); // Draw the ball
        sf::CircleShape getPelota(void);
};

#endif // PELOTA_H
