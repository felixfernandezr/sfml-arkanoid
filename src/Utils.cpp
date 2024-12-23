#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

// Sleep for a given number of seconds
void Utils::sleepSegundos(unsigned int segundos) {
    std::this_thread::sleep_for(std::chrono::seconds(segundos));
}

// Static function to show a countdown in the middle of the screen
void Utils::cuentaRegresivaRecursi(unsigned int inicio, sf::RenderWindow& ventana)
{
    if(inicio <= 0) return;

    // Load font
    sf::Font fuente;
    if (!fuente.loadFromFile("assets/fonts/xirod.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Create a semi-transparent overlay rectangle to "erase" the previous number
    sf::RectangleShape parche(sf::Vector2f(33, 33));
    parche.setPosition(390, 236); // Position it where the countdown is displayed
    parche.setFillColor(sf::Color(0, 0, 255, 255));

    std::string txt1 = "Returning to Game In:";
    sf::Text returnTxt(txt1, fuente, 32);
    returnTxt.setPosition(128, 200);

    std::string txt2 = std::to_string(inicio);
    sf::Text cNumTxt(txt2, fuente, 32);
    cNumTxt.setPosition(390, 236);

    ventana.draw(parche);
    ventana.draw(returnTxt);
    ventana.draw(cNumTxt);
    ventana.display();

    sleepSegundos(1); // Sleep for 1 second before showing the next number

    cuentaRegresivaRecursi(inicio - 1, ventana); // Recursive call with counter decreased by 1
}




