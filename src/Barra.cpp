#include "Barra.h"
#include <iostream>
#include <windows.h>

// Constructor initializes bar X,Y position and width
Barra::Barra(float inicialX)
{
    this->barra.setSize(sf::Vector2f(100.f, 20.f)); // Width = 100, Height = 20
    this->barra.setFillColor(sf::Color::Red);
    this->barra.setPosition(inicialX, 550.f); // Set position near the bottom
    this->velocidad = 20.0f;
}

// Bar movement
void Barra::mover(int direccion, const sf::RenderWindow& ventana)
{
    // Get current position
    sf::Vector2f posicionActual = this->barra.getPosition();

    // Compute new position
    float nuevaPosX = posicionActual.x + (direccion * this->velocidad);

    // Ensure the bar stays within the window bounds
    if (nuevaPosX >= 0 && nuevaPosX + this->barra.getSize().x <= ventana.getSize().x)
    {
        this->barra.setPosition(nuevaPosX, posicionActual.y);
    }
}

// Bar rendering
void Barra::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(this->barra);
}

void Barra::reiniciar()
{
     this->barra.setPosition(this->inicialPosX, 550.f);
}

sf::RectangleShape Barra::getBarra()
{
    return this->barra;
}
