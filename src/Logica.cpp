#include "Logica.h"
#include <iostream>

#include "Utils.h"

Logica::Logica() {}

// Main game update logic
bool Logica::juegoUpdate(sf::RenderWindow& ventana, Pelota* pelota, Barra* barra, Obstaculo* obstaculos, unsigned int* puntaje, unsigned int* record, unsigned int* vidas)
{

    sf::CircleShape pelotaUpdate = pelota->getPelota();

    // Check for collision with obstacles
    if (obstaculos->checkColision(pelotaUpdate.getPosition().x, pelotaUpdate.getPosition().y))
    {
        pelota->rebotarY(); // Bounce the ball vertically
        *puntaje += 10; // Increment score

        if (*puntaje > *record) // Check if new record
        {
            *record = *puntaje;
        }
    }

    // Check collisions with walls
    sf::Vector2f pelotaPosicion = pelotaUpdate.getPosition();

    if (pelotaPosicion.y <= 34) // Top wall
    {
        pelota->rebotarY();
    }
    if (pelotaPosicion.x <= 0 || pelotaPosicion.x >= 800)// Left or right wall (assuming 800px screen width)
    {
        pelota->rebotarX();
    }

    // Check collision with the bar
    sf::RectangleShape barraUpdate = barra->getBarra();
    sf::Vector2f barraSize = barraUpdate.getSize();
    sf::Vector2f barraPosicion = barraUpdate.getPosition();
    float barraAncho = barraSize.x;
    float barraAlto = barraSize.y;

    if (pelotaPosicion.y >= barraPosicion.y && pelotaPosicion.y <= barraPosicion.y + barraAlto)
    {
        if (pelotaPosicion.x >= barraPosicion.x && pelotaPosicion.x <= barraPosicion.x + barraAncho)
        {
            pelota->rebotarY(); // Bounce vertically
        }
    }

    // Check if ball missed the bar (bottom of the screen)
    if (pelotaPosicion.y >= 600) // Assuming 600px screen height
    {
        *vidas = *vidas - 1; // Reduce lives
        *puntaje = 0; // Reset score
        if (*vidas > 0)
        {
            Utils::cuentaRegresivaRecursi(3, ventana); // Countdown
        }
        pelota->reiniciar(); // Reset ball position
    }

    // Check if the game is over (no lives or level complete)
    if (*vidas < 1 || obstaculos->checkNivelCompleto())
    {
        return true; // End game
    }

    return false; // Continue game
}
