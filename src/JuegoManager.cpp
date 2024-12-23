#include "JuegoManager.h"
#include <iostream>
#include <conio.h>

#include "Juego.h"
#include "Utils.h"

// Class constructor
JuegoManager::JuegoManager() : nivelActual(1) // Setting level to first
{
    this->estadoActual = EstadoJuego::MenuInico; // First state start menu
    this->gameOver = false;
}

// This function serves as a state handler for the game
void JuegoManager::jugar()
{
    while(!this->gameOver) // Done while gameOver is false
    {
        try
        {
            switch(this->estadoActual)
            {
                case EstadoJuego::Play:
                    this->inicializarNivel(); // Level handling
                    this->juego.comenzar(); // Game-loop
                    this->nivelActual++; // Level raise
                    this->juego.pelota.reiniciar(); // Ball position reset

                    if(this->nivelActual < 5 && this->juego.vidas > 0) // Compares to 5 because nivelActual is raised before if statement
                    {
                        this->cambiarEstado(EstadoJuego::NivelCompleto);
                    }
                    else if(this->juego.vidas == 0)
                    {
                        this->resetValores();
                        this->cambiarEstado(EstadoJuego::GameOver);
                    }
                    else
                    {
                        //this->resetValores();
                        this->cambiarEstado(EstadoJuego::FinDelJuego);
                    }
                    break;

                case EstadoJuego::MenuInico:
                    this->mostrarMenuInicio(); // call to "ui" function
                    break;

                case EstadoJuego::NivelCompleto:
                    this->mostrarNivelCompleto();
                    this->cambiarEstado(EstadoJuego::Play);
                    break;

                case EstadoJuego::GameOver:
                    this->mostrarGameOver(); // Show game over "ui"
                    this->cambiarEstado(EstadoJuego::MenuInico);
                    break;

                case EstadoJuego::FinDelJuego:
                    this->mostrarPantallaFin(); // Show end screen "ui"
                    this->mostrarCreditos(); // Show game credits
                    this->resetValores();
                    this->cambiarEstado(EstadoJuego::MenuInico);
                    break;

                case EstadoJuego::Creditos:
                    this->mostrarCreditos();
                    this->cambiarEstado(EstadoJuego::MenuInico);
                    break;

                case EstadoJuego::Exit:
                    this->mostrarPantallaExit(); // If user presses 'y' gameOver is set to true and ends program,
                    this->cambiarEstado(EstadoJuego::MenuInico); // Back to main menu
                    break;
            }
        }
        catch (const std::exception& e)
        {
            this->cambiarEstado(EstadoJuego::MenuInico);
        }
    }
}

// Level handler
void JuegoManager::inicializarNivel() {
    switch (this->nivelActual) {
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
            this->cambiarEstado(EstadoJuego::GameOver); // No more levels. When level > 3 this catches game end.
            break;
    }
}

 // Start screen UI
void JuegoManager::mostrarMenuInicio()
{
    system("cls");
    while (true) {
        // Clear the screen
        std::cout << "\033[2J\033[1;1H";

        // Display menu options
        std::cout << "====================\n";
        std::cout << "  Welcome to Arkanot  \n";
        std::cout << "====================\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Show Credits\n";
        std::cout << "3. Exit Game\n";
        std::cout << "Select an option: ";

        // Wait for user input
        char choice = _getch();
        switch (choice) {
            case '1':
                this->resetValores();
                cambiarEstado(EstadoJuego::Play);
                return; // Exit the menu function
            case '2':
                cambiarEstado(EstadoJuego::Creditos);
                return;
            case '3':
                cambiarEstado(EstadoJuego::Exit);
                return;
            default:
                std::cout << "\nInvalid option. Please try again.\n";
                Utils::sleepSegundos(1);
        }
    }
}

void JuegoManager::mostrarNivelCompleto()
{
    system("cls");
    std::cout << "Well Done! You Completed Level " << this->nivelActual - 1 << "!" << std::endl;
    std::cout << "Your Score is Currently " << this->juego.record << "!" << std::endl;
    std::cout << "Press Any Key to Continue" << std::endl;

    // Wait for user input
    _getch();
}

// End screem UI
void JuegoManager::mostrarGameOver()
{
    system("cls");
    std::cout << "Game Over!" << std::endl;
    std::cout << "Your Best Score Was: " << this->juego.record << "!" << std::endl;
    std::cout << "Press Any Key to Exit" << std::endl;

    // Wait for user input
    _getch();
}

void JuegoManager::mostrarPantallaFin()
{
    system("cls");
    std::cout << "Congratulations! You Won the Game!" << std::endl;
    std::cout << "Your Best Score Was: " << this->juego.record << "!" << std::endl;
    std::cout << "Press Any Key and Go to Credits" << std::endl;

    // Wait for user input
    _getch();
}

void JuegoManager::mostrarCreditos()
{
    system("cls");
    std::cout << "A JKNBH777 Creation" << std::endl;
    std::cout << "Press Any Key and Go to Main Menu" << std::endl;

    // Wait for user input
    _getch();
}

void JuegoManager::mostrarPantallaExit()
{
    system("cls");
    std::cout << "You Are About to Exit the Game. Are You Sure?" << std::endl;
    std::cout << "Press 'y' to Confirm or Any Key and Go to Main Menu." << std::endl;

    char tecla = _getch();
    if (tecla == 'y')
    {
        this->gameOver = true;
    }
}

// Change game state
void JuegoManager::cambiarEstado(EstadoJuego nuevoEstado)
{
    this->estadoActual = nuevoEstado;
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

