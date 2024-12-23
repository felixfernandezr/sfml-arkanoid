#include "Pelota.h"
#include <iostream>
#include <windows.h>

// Ball class with fundamental logic
Pelota::Pelota()
{
    this->posicion = sf::Vector2f(200.f, 150.f); // Initial position (center of screen)
    this->direccion = sf::Vector2f(1.f, 1.f); // Initial direction
    this->velocidad = 4.f; // Initial speed

    this->pelota.setRadius(10.f); // Set radius of the ball
    this->pelota.setFillColor(sf::Color::White); // Set color
    this->pelota.setOrigin(10.f, 10.f); // Center origin for proper positioning
    this->pelota.setPosition(this->posicion); // Initialize position
}

// Moving ball
void Pelota::mover(void)
{
    this->posicion += this->direccion * this->velocidad; // Update position based on direction and speed
    this->pelota.setPosition(this->posicion); // Update graphical position

    // Debug log
    //std::cout << "Ball Position: " << this->posicion.x << ", " << this->posicion.y << std::endl;
}

// Reset ball to initial position and direction
void Pelota::reiniciar()
{
    this->posicion = sf::Vector2f(200.f, 100.f); // Reset position (center of screen)
    this->direccion = sf::Vector2f(1.f, 1.f); // Reset direction
    this->pelota.setPosition(this->posicion); // Update graphical position*/
}

// Bounce in the Y axis
void Pelota::rebotarY()
{
    this->direccion.y = -this->direccion.y; // Reverse Y direction
}

// Bounce in the X axis
void Pelota::rebotarX()
{
    this->direccion.x = -this->direccion.x; // Reverse X direction
}

// Render the ball
void Pelota::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(this->pelota); // Draw the ball on the window
}

sf::CircleShape Pelota::getPelota()
{
    return this->pelota;
}

