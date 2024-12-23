#include <SFML/Graphics.hpp>
#include "JuegoManager.h"

int main() {
    // Initialize the game object (this will initialize other objects like ball, bar, obstacles, etc.)
    JuegoManager juegoManager;

    // Start the game loop
    juegoManager.comenzar();  // Calls the comenzar() function of JuegoManager class

    return 0;
}
