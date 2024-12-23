#include <SFML/Graphics.hpp>
#include "Juego.h"

int main() {
    // Create the game window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Arkanoid-like Game");

    // Initialize the game object (this will initialize other objects like ball, bar, obstacles, etc.)
    Juego juego;

    // Start the game loop
    juego.comenzar();  // Calls the comenzar() function of Juego class

    return 0;
}
