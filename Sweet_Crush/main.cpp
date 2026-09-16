#include <iostream>
#include <ctime>
#include "memoria.h"
#include "bitwise.h"
#include "interfaz.h"
#include "logica.h"

using namespace std;

int main() {
    srand(time(0));   // <-- una sola vez, antes de generar nada

    int filas = 5, columnas = 5;
    int bytesReservados = 0;

    unsigned char* tablero = Crear_tablero(filas, columnas, &bytesReservados);
    Rellenar_tablero(tablero, filas, columnas);

    cout << "Tablero inicial:\n";
    Mostrar_tablero(tablero, filas, columnas);

    Liberar_tablero(tablero);
    return 0;
}