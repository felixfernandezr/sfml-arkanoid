#include "EstadoManager.h"
#include <iostream>

EstadoManager::EstadoManager() : estadoActual(EstadoJuego::MenuInico) {}

void EstadoManager::cambiarEstado(EstadoJuego nuevoEstado)
{
    system("cls");
        std::cout << "FROM STATE HANDLER CAMBIAR ESTADO Current State: " << static_cast<int>(nuevoEstado) << std::endl;
        system("pause");
    this->estadoActual = nuevoEstado;
}

EstadoJuego EstadoManager::getEstadoActual()
{
    return this->estadoActual;
}
