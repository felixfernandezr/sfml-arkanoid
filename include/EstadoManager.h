#ifndef ESTADOMANAGER_H_INCLUDED
#define ESTADOMANAGER_H_INCLUDED

#include "EstadoJuego.h"

class EstadoManager
{
    public:
        EstadoManager();
        void cambiarEstado(EstadoJuego nuevoEstado);
        EstadoJuego getEstadoActual();

    private:
        EstadoJuego estadoActual;
};

#endif // ESTADOMANAGER_H_INCLUDED
