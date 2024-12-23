#ifndef JUEGOMANAGER_H_INCLUDED
#define JUEGOMANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>

#include "EstadoJuego.h"
#include "Juego.h"

class JuegoManager {

    public:
        JuegoManager();

        void comenzar(void);
        void jugar(sf::RenderWindow& ventana);
        void inicializarNivel(void);

        void mostrarMenuInicio(sf::RenderWindow& ventana);
        void mostrarNivelCompleto(sf::RenderWindow& ventana);
        void mostrarGameOver(sf::RenderWindow& ventana);
        void mostrarPantallaFin(sf::RenderWindow& ventana);
        void mostrarCreditos(sf::RenderWindow& ventana);
        void mostrarPantallaExit(sf::RenderWindow& ventana);

        void cambiarEstado(EstadoJuego nuevoEstado);
        void resetValores(void);

    private:
        unsigned int nivelActual;
        EstadoJuego estadoActual;
        Juego juego;
        Niveles niveles;
        sf::Font fuente;
        bool gameOver;
};

#endif // JUEGOMANAGER_H_INCLUDED
