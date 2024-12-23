#ifndef JUEGOMANAGER_H_INCLUDED
#define JUEGOMANAGER_H_INCLUDED

#include "EstadoJuego.h"
#include "Juego.h"

class JuegoManager {
    public:
        JuegoManager();
        void jugar();
        void inicializarNivel(void);
        void mostrarMenuInicio(void);
        void mostrarNivelCompleto(void);
        void mostrarGameOver(void);
        void mostrarPantallaFin(void);
        void mostrarCreditos(void);
        void mostrarPantallaExit(void);
        void cambiarEstado(EstadoJuego nuevoEstado);
        void resetValores(void);

    private:
        Juego juego;
        EstadoJuego estadoActual;
        Niveles niveles;
        unsigned int nivelActual;
        bool gameOver;
};

#endif // JUEGOMANAGER_H_INCLUDED
