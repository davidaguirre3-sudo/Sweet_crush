#include "memoria.h"

int Calcular_bytesnecesarios(int filas, int columnas) {
    int bitsNecesarios = filas * columnas * 3;
    int bytesNecesarios = (bitsNecesarios + 7) / 8;
    return bytesNecesarios;
}

unsigned char* Crear_tablero(int filas, int columnas, int* bytesReservados) {
    int bytes = Calcular_bytesnecesarios(filas, columnas);
    unsigned char* tablero = new unsigned char[bytes];

    for (int i = 0; i < bytes; i++) {
        tablero[i] = 0;
    }

    *bytesReservados = bytes;
    return tablero;
}

void Liberar_tablero(unsigned char* tablero) {
    delete[] tablero;
}