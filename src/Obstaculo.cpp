#include "Obstaculo.h"
#include <iostream>
#include <windows.h>

// Constructor initializes obstacle width
Obstaculo::Obstaculo(unsigned int ancho) : ancho(ancho) {}

// Initialize obstacles based on grid
void Obstaculo::inicializarObstaculos(const std::vector<std::vector<unsigned int>>& nivel)
{
    this->grilla = nivel;
    this->filas = nivel.size();
    this->columnas = nivel[0].size();

    // Resize template grid
    this->grilla.resize(this->filas, std::vector<unsigned int>(this->columnas));
    // Resize obstacle shapes
    this->obstaculos.resize(this->filas, std::vector<sf::RectangleShape>(this->columnas));

    for (unsigned int i = 0; i < this->filas; i++)
    {
        for (unsigned int j = 0; j < this->columnas; j++)
        {
            //std::cout << this->grilla[i][j] << "->";
            if (this->grilla[i][j] > 0) // Only initializes for existing obstacles
                this->grilla[i][j] = this->getNumeroAleatorio(1,3); // Random strength (0 = no obstacle, 1-3 = obstacle strength)
            //std::cout << this->grilla[i][j] << " | ";
        }
        //std::cout << std::endl;
    }
    //system("pause");
}

// Check for collision with ball
bool Obstaculo::checkColision(float pelotaX, float pelotaY)
{
    for (unsigned int i = 0; i < this->filas; i++)
    {
        for (unsigned int j = 0; j < this->columnas; j++)
        {
            if (this->grilla[i][j] > 0) // If obstacle exists
            {
                sf::RectangleShape& obstaculo = this->obstaculos[i][j];
                sf::FloatRect limites = obstaculo.getGlobalBounds(); // Get positions of obstacle bounds

                // Check collision with ball
                if (limites.contains(pelotaX, pelotaY))
                {
                    this->grilla[i][j]--; // Reduce strength

                    return true;
                }
            }
        }
    }
    return false;
}



void Obstaculo::dibujar(sf::RenderWindow& ventana)
{
    for (unsigned int i = 0; i < this->filas; i++)
    {
        for (unsigned int j = 0; j < this->columnas; j++)
        {
            sf::RectangleShape obstaculo;

            if (this->grilla[i][j] > 0)
            {
                obstaculo.setSize(sf::Vector2f(this->ancho, 20.f)); // Setting width and fixed height
                obstaculo.setPosition(j * this->ancho, 34 + (i * 22.f)); // Setting position based on grid
                obstaculo.setFillColor(sf::Color::White); // Default color

                if (this->grilla[i][j] == 3)
                    obstaculo.setFillColor(sf::Color::Green); // Hard strength
                if (this->grilla[i][j] == 2)
                    obstaculo.setFillColor(sf::Color::Yellow); // Medium strength
                else if (this->grilla[i][j] == 1)
                    obstaculo.setFillColor(sf::Color::Red);    // Weak strength

                this->obstaculos[i][j] = obstaculo;
            }
            else
            {
                obstaculo.setSize(sf::Vector2f(0, 0));     // Remove obstacle
                this->obstaculos[i][j] = obstaculo;
            }

            ventana.draw(this->obstaculos[i][j]);
        }
    }
}

// Checks if every position of the vector is 0 (no obstacle)
bool Obstaculo::checkNivelCompleto()
{
    for (unsigned int i = 0; i < this->filas; i++)
    {
        for (unsigned int j = 0; j < this->columnas; j++)
        {
            if(this->grilla[i][j] > 0)
            {
                return false;
            }
        }
    }

    return true;
}

unsigned int Obstaculo::getNumeroAleatorio(unsigned int a, unsigned int b)
{
    static bool first = true;
    if (first) {
        srand(static_cast<unsigned int>(time(NULL)));
        first = false;
    }
    return a + rand() % (b - a + 1);
}
