#include <iostream>
#include "memoria.h"
#include "bitwise.h"

using namespace std;

int main() {
    int filas = 5, columnas = 5;
    int bytesReservados = 0;

    unsigned char* tablero = Crear_tablero(filas, columnas, &bytesReservados);
    cout << "Bytes reservados: " << bytesReservados << "\n";

    Escribir_ficha(tablero, columnas, 0, 0, 5);
    Escribir_ficha(tablero, columnas, 4, 4, 6);

    cout << "Ficha (0,0) = " << Extraer_ficha(tablero, columnas, 0, 0) << "\n";
    cout << "Ficha (4,4) = " << Extraer_ficha(tablero, columnas, 4, 4) << "\n";
    cout << "Ficha (2,2) = " << Extraer_ficha(tablero, columnas, 2, 2) << " (deberia ser 0)\n";

    Liberar_tablero(tablero);
    return 0;
}