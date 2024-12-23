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
        Juego();
        void comenzar(); // Starts the game

    private:
        void juegoLoop(sf::RenderWindow& ventana);
        void eventoHandler(sf::RenderWindow& ventana);
        void juega(sf::RenderWindow& ventana);
        void renders(sf::RenderWindow& ventana);

        void funcionPausa(sf::RenderWindow& ventana);
        void funcionSalir(sf::RenderWindow& ventana);
        void pausaRecursi(void);

        Barra barra;
        Pelota pelota;
        Obstaculo obstaculos;
        Logica logica;
        Niveles nivel;

        unsigned int puntaje;
        unsigned int record;
        unsigned int vidas;

        bool finDelJuego;
        EstadoJuego estadoJuego;
};

#endif // JUEGO_H_INCLUDED
