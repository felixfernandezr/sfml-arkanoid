#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Pelota.h"
#include "Barra.h"
#include "Cancha.h"
#include "Obstaculo.h"
#include "Logica.h"
#include "Niveles.h"
#include "EstadoManager.h"

class Juego
{
    public:
        Juego(EstadoJuego& estadoActual);

        void juegoLoop(sf::RenderWindow& ventana);
        void eventoHandler(sf::RenderWindow& ventana);
        void juega(sf::RenderWindow& ventana);
        void rendersJuego(sf::RenderWindow& ventana);

        void funcionPausaInGame(sf::RenderWindow& ventana);
        void funcionSalirInGame(sf::RenderWindow& ventana);

        Barra barra;
        Pelota pelota;
        Obstaculo obstaculos;
        Logica logica;
        Niveles nivel;
        EstadoJuego& estadoJuego;

        unsigned int puntaje;
        unsigned int record;
        unsigned int vidas;
        unsigned int nivelActual;
        bool finDelJuego = false;
};

#endif // JUEGO_H_INCLUDED
