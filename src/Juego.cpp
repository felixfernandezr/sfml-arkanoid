#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>

#include "Utils.h"

// Constructor
Juego::Juego(): barra(400), obstaculos(400), logica(), finDelJuego(false), estadoJuego(EstadoJuego::Juega) // Initialize with Bar in axis x=40 and Obstacles width = 4
{
    this->puntaje = 0; // Score and record = 0
    this->record = 0;
    this->vidas = 3;
}

void Juego::comenzar()
{
    // Create the game window
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "SFML Game");

    // Run the game loop
    this->juegoLoop(ventana);
}

void Juego::juegoLoop(sf::RenderWindow& ventana)
{
    // Frame rate control
    sf::Clock clock;

    this->obstaculos.inicializarObstaculos(this->nivel.nivel1());

     // Main game loop
    while (ventana.isOpen())
    {
        this->eventoHandler(ventana);

        if (this->estadoJuego == EstadoJuego::Juega)
        {
            this->juega(ventana);
        }

        this->renders(ventana);

        // Frame rate control (60 FPS)
        sf::Time elapsed = clock.restart();
        sf::sleep(sf::seconds(1.f / 60.f) - elapsed);
    }
}

void Juego::eventoHandler(sf::RenderWindow& ventana)
{
    sf::Event evento;
    while (ventana.pollEvent(evento))
    {
        if (evento.type == sf::Event::Closed)
            ventana.close();

        if (evento.type == sf::Event::KeyPressed)
        {
            switch (evento.key.code)
            {
                case sf::Keyboard::P:
                    this->funcionPausa(ventana);
                    break;
                case sf::Keyboard::Escape:
                    this->funcionSalir(ventana);
                    break;
                case sf::Keyboard::A:
                    this->barra.mover(-1, ventana);
                    break;
                case sf::Keyboard::D:
                    this->barra.mover(1, ventana);
                    break;
                default:
                    break;
            }
        }
    }
}

void Juego::juega(sf::RenderWindow& ventana)
{
    this->finDelJuego = this->logica.juegoUpdate(ventana, &pelota, &barra, &obstaculos, &puntaje, &record, &vidas);

    if(this->finDelJuego)
    {
        this->estadoJuego = EstadoJuego::Salir;
    }

    this->pelota.mover();
}

void Juego::renders(sf::RenderWindow& ventana)
{
    ventana.clear(sf::Color::Blue);

    // Create a font for text rendering
    sf::Font fuente;
    if (!fuente.loadFromFile("assets/fonts/xirod.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Display the score
    sf::Text puntajeTxt;
    puntajeTxt.setFont(fuente);
    puntajeTxt.setCharacterSize(24);
    puntajeTxt.setFillColor(sf::Color::White);
    puntajeTxt.setString("Puntaje: " + std::to_string(this->puntaje) +
                         "    Record: " + std::to_string(this->record) +
                         "    Vidas: " + std::to_string(this->vidas));
    ventana.draw(puntajeTxt);

    // Draw game elements
    obstaculos.dibujar(ventana);
    pelota.dibujar(ventana);
    barra.dibujar(ventana);

    ventana.display();
}

void Juego::funcionPausa(sf::RenderWindow& ventana)
{
    this->estadoJuego = EstadoJuego::Pausa;

    // Create a font for text rendering
    sf::Font fuente;
    if (!fuente.loadFromFile("assets/fonts/xirod.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    std::string txt1 = "      Game Paused\nPress P to Resume";
    sf::Text pausaTxt(txt1, fuente, 32);
    pausaTxt.setPosition(150, 200);

    while (this->estadoJuego == EstadoJuego::Pausa)
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::P)
            {
                this->estadoJuego = EstadoJuego::Juega;
            }
        }

        ventana.draw(pausaTxt);
        ventana.display();
    }
}

void Juego::funcionSalir(sf::RenderWindow& ventana)
{
    this->estadoJuego = EstadoJuego::Salir;

    // Create a font for text rendering
    sf::Font fuente;
    if (!fuente.loadFromFile("assets/fonts/xirod.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Create a semi-transparent overlay rectangle to "erase" the previous number
    sf::RectangleShape parche(sf::Vector2f(400, 33));
    parche.setPosition(200, 200); // Position it where the countdown is displayed
    parche.setFillColor(sf::Color(0, 0, 255, 255));

    // Creating text
    std::string txt1 = "Exit Game? (Y/N)";
    sf::Text txtSalir(txt1, fuente, 32);
    txtSalir.setPosition(200, 200);

    // Wait for user input
    while (this->estadoJuego == EstadoJuego::Salir)
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code == sf::Keyboard::Y)
                {
                    ventana.close();
                }
                else if (evento.key.code == sf::Keyboard::N)
                {
                    this->funcionPausa(ventana);
                }
            }
        }
        ventana.draw(parche);
        ventana.draw(txtSalir);
        ventana.display();
    }
}










