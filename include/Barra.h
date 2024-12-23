#ifndef BARRA_H
#define BARRA_H
#include <SFML/Graphics.hpp>

#include "Dupla.h"

class Barra
{

    private:
        sf::RectangleShape barra; // Visual representation of the bar
        float velocidad;              // Speed for movement

    public:
        Barra(float inicialPosX);
        float inicialPosX;

        void mover(int direccion, const sf::RenderWindow& ventana);
        void moverIzquierda(void);
        void moverDerecha(void);
        void dibujar(sf::RenderWindow& ventana);
        void reiniciar(void);
        sf::RectangleShape getBarra(void);
};

#endif // BARRA_H
