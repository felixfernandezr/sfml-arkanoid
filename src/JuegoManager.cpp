#include "JuegoManager.h"
#include <iostream>
#include <conio.h>
#include <SFML/Audio.hpp>

#include "Juego.h"
#include "Utils.h"

// Class constructor
JuegoManager::JuegoManager() : nivelActual(1), estadoActual(EstadoJuego::MenuInico), juego(estadoActual) // Setting level to first
{
    this->gameOver = false;

    // Create a font for text rendering
    if (!this->fuente.loadFromFile("assets/fonts/xirod.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }
}

void JuegoManager::comenzar()
{
    // Create the game window
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "SFML Game");

    // Run the game loop
    this->jugar(ventana);
}

// This function serves as a state handler for the game
void JuegoManager::jugar(sf::RenderWindow& ventana)
{
    while(!this->gameOver) // Done while gameOver is false
    {
        try
        {
            switch(this->estadoActual)
            {
                case EstadoJuego::Juega:
                    this->inicializarNivel(); // Level handling
                    this->inicializarMusica();
                    this->juego.juegoLoop(ventana); // Game-loop
                    this->nivelActual++; // Level raise
                    this->juego.finDelJuego = false;
                    this->juego.pelota.reiniciar(); // Ball position reset

                    // Compares to 5 because nivelActual is raised before if statement
                    if(this->nivelActual < 4 && this->juego.vidas > 0)
                        this->estadoActual = EstadoJuego::NivelCompleto;
                    else if(this->juego.vidas == 0)
                        this->estadoActual = EstadoJuego::GameOver;
                    else
                        this->estadoActual = EstadoJuego::FinDelJuego;

                    break;

                case EstadoJuego::MenuInico:
                    this->mostrarMenuInicio(ventana); // call to "ui" function
                    break;

                case EstadoJuego::NivelCompleto:
                    this->mostrarNivelCompleto(ventana);
                    //this->estadoActual = EstadoJuego::Juega;
                    break;

                case EstadoJuego::GameOver:
                    this->mostrarGameOver(ventana); // Show game over "ui"
                    this->resetValores();
                    //this->estadoActual = EstadoJuego::MenuInico;
                    break;

                case EstadoJuego::FinDelJuego:
                    this->mostrarPantallaFin(ventana); // Show end screen "ui"
                    this->mostrarCreditos(ventana); // Show game credits
                    this->resetValores();
                    //this->estadoActual = EstadoJuego::MenuInico;
                    break;

                case EstadoJuego::Creditos:
                    this->mostrarCreditos(ventana);
                    //this->estadoActual = EstadoJuego::MenuInico;
                    break;

                case EstadoJuego::Salir:
                    this->mostrarPantallaExit(ventana); // If user presses 'y' gameOver is set to true and ends program,
                    //this->estadoActual = EstadoJuego::MenuInico; // Back to main menu
                    break;
            }
        }
        catch (const std::exception& e)
        {
            this->estadoActual = EstadoJuego::MenuInico;
        }
    }
}

// Level handler
void JuegoManager::inicializarNivel()
{
    switch (this->nivelActual)
    {
        case 1:
            this->juego.obstaculos.inicializarObstaculos(niveles.nivel1()); // Sends a template of obstacle distribution (check Niveles niveles.nivel1())
            break;
        case 2:
            this->juego.obstaculos.inicializarObstaculos(niveles.nivel2()); // This templates only have 1s and 0s
            break;
        case 3:
            this->juego.obstaculos.inicializarObstaculos(niveles.nivel3()); // Then randomized in Obstaculos obstaculos.inicializarObstaculos()
            break;
        default:
            this->estadoActual = EstadoJuego::GameOver; // No more levels. When level > 3 this catches game end.
            break;
    }
}

void JuegoManager::inicializarMusica()
{
    std::string rutaMusica = "";

    if(this->nivelActual == 1)
    {
        rutaMusica = "assets/sounds/nivel1.mp3";
    }
    else if(this->nivelActual == 2)
    {
        rutaMusica = "assets/sounds/nivel2.mp3";
    }
    else if(this->nivelActual == 3)
    {
        rutaMusica = "assets/sounds/nivel3.mp3";
    }

    // Load the music file
    if (!this->musicaJuego.openFromFile(rutaMusica))
    {
        std::cerr << "Error: Could not load music file!" << std::endl;
        return;
    }

    this->musicaJuego.setLoop(true);
    this->musicaJuego.setVolume(50.f);
    this->musicaJuego.play();
}

 // Start screen UI
void JuegoManager::mostrarMenuInicio(sf::RenderWindow& ventana)
{
    // Load the music file
    if (!this->musicaJuego.openFromFile("assets/sounds/menuInicio.mp3"))
    {
        std::cerr << "Error: Could not load music file!" << std::endl;
        return;
    }

    // Prepare main menu text
    std::string divLine = "======================================";
    std::string txt1 = divLine + "\nWelcome to Arkanot  \n" + divLine + "\n       1.  Start Game\n       2. Show Credits\n       3. Exit Game\n    Select an option: ";
    sf::Text menuInicioTxt(txt1, this->fuente, 24);
    menuInicioTxt.setPosition(200, 180);
    menuInicioTxt.setFillColor(sf::Color::White);

    this->musicaJuego.setVolume(50.f);
    this->musicaJuego.play();

    while (this->estadoActual == EstadoJuego::MenuInico)
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::KeyPressed)
            {
                switch (evento.key.code)
                {
                    case sf::Keyboard::Num1:
                        this->estadoActual = EstadoJuego::Juega;
                        return;
                    case sf::Keyboard::Num2:
                        this->estadoActual = EstadoJuego::Creditos;
                        return;
                    case sf::Keyboard::Num3:
                        this->estadoActual = EstadoJuego::Salir;
                        return;
                    default:
                        break;
                }
            }
        }
        ventana.clear(sf::Color::Blue);
        ventana.draw(menuInicioTxt);
        ventana.display();
    }
}

void JuegoManager::mostrarNivelCompleto(sf::RenderWindow& ventana)
{
    // Load the music file
    if (!this->musicaJuego.openFromFile("assets/sounds/nivelCompleto.mp3"))
    {
        std::cerr << "Error: Could not load music file!" << std::endl;
        return;
    }

    // Prepare level completed text
    std::string txt1 = "Well Done! You Completed Level " + std::to_string(this->nivelActual - 1) + "!";
    sf::Text nivelCompletoTxt(txt1, this->fuente, 24);
    nivelCompletoTxt.setPosition(60, 200);
    nivelCompletoTxt.setFillColor(sf::Color::White);

    ventana.draw(nivelCompletoTxt);
    ventana.display();

    this->musicaJuego.setVolume(50.f);
    this->musicaJuego.play();

    Utils::sleepSegundos(3);

    this->estadoActual = EstadoJuego::Juega;
}

// End screem UI
void JuegoManager::mostrarGameOver(sf::RenderWindow& ventana)
{
    // Load the music file
    if (!this->musicaJuego.openFromFile("assets/sounds/gameOver.mp3"))
    {
        std::cerr << "Error: Could not load music file!" << std::endl;
        return;
    }

    // Prepare game over text
    std::string txt1 = "         Game Over!\nYour Record Was: " + std::to_string(this->juego.record);
    sf::Text gameOverTxt(txt1, this->fuente, 24);
    gameOverTxt.setPosition(200, 200);
    gameOverTxt.setFillColor(sf::Color::White);

    ventana.clear(sf::Color::Blue);
    ventana.draw(gameOverTxt);
    ventana.display();

    this->musicaJuego.setVolume(50.f);
    this->musicaJuego.play();

    Utils::sleepSegundos(3);

    this->estadoActual = EstadoJuego::MenuInico;
}

void JuegoManager::mostrarPantallaFin(sf::RenderWindow& ventana)
{
    // Prepare end screen text
    std::string txt1 = "  Congratulations!\n You Won the Game!!!\nYour Record Was: " + std::to_string(this->juego.record);
    sf::Text endScreenTxt(txt1, this->fuente, 24);
    endScreenTxt.setPosition(200, 200);
    endScreenTxt.setFillColor(sf::Color::White);

    ventana.clear(sf::Color::Blue);
    ventana.draw(endScreenTxt);
    ventana.display();

    Utils::sleepSegundos(3);

    this->estadoActual = EstadoJuego::Creditos;
}

void JuegoManager::mostrarCreditos(sf::RenderWindow& ventana)
{
    // Prepare credits text
    std::string txt1 = "              A JKNBH777 Creation\n\nPress Any Key and Go to Main Menu";
    sf::Text creditsTxt(txt1, this->fuente, 24);
    creditsTxt.setPosition(50, 200);
    creditsTxt.setFillColor(sf::Color::White);

    while (this->estadoActual == EstadoJuego::Creditos)
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::KeyPressed)
            {
                this->estadoActual = EstadoJuego::MenuInico;
            }
        }
        ventana.clear(sf::Color::Blue);
        ventana.draw(creditsTxt);
        ventana.display();
    }
}

void JuegoManager::mostrarPantallaExit(sf::RenderWindow& ventana)
{
    // Prepare exit text
    std::string txt1 = "You Are About to Exit the Game.\n                Are You Sure?\n           Press 'y' to Confirm\nor Any Key and Go to Main Menu.";
    sf::Text exitTxt(txt1, this->fuente, 24);
    exitTxt.setPosition(88, 200);
    exitTxt.setFillColor(sf::Color::White);

    while (this->estadoActual == EstadoJuego::Salir)
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Y)
                ventana.close();
            else if (evento.type == sf::Event::KeyPressed)
                this->estadoActual = EstadoJuego::MenuInico;
        }
        ventana.clear(sf::Color::Blue);
        ventana.draw(exitTxt);
        ventana.display();
    }
}

//Reset game default values
void JuegoManager::resetValores()
{
    this->nivelActual = 1;

    this->juego.puntaje = 0;
    this->juego.record = 0;
    this->juego.vidas = 3;
    this->juego.barra.reiniciar();
    this->juego.pelota.reiniciar();
}

