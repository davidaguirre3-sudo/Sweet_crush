#include <iostream>
#include <ctime>
#include "memoria.h"
#include "bitwise.h"
#include "interfaz.h"
#include "logica.h"
#include "estadisticas.h"

using namespace std;

int main() {
    srand(time(0));

    int filas, columnas;
    cout << "Filas iniciales: ";  cin >> filas;
    cout << "Columnas iniciales: "; cin >> columnas;

    int capacidadBytes = 0;
    unsigned char* tablero = Crear_tablero(filas, columnas, &capacidadBytes);

    int eliminacionesDirectas = 0, combinacionesTotales = 0, fichasTotales = 0, cascadasTotales = 0, puntuacion = 0;
    int combinacionesEstaJugada = 0, fichasEstaJugada = 0, cascadasEstaJugada = 0;

    bool* marcado = new bool[filas * columnas];
    Rellenar_tablero(tablero, filas, columnas, capacidadBytes);
    Procesar_cascadas(tablero, filas, columnas, capacidadBytes, marcado,
                      &combinacionesTotales, &fichasTotales, &cascadasTotales,
                      &combinacionesEstaJugada, &fichasEstaJugada, &cascadasEstaJugada,
                      &puntuacion, true);

    bool jugando = true;
    while (jugando) {
        cout << "\n----------------------------\n";
        Mostrar_tablero(tablero, filas, columnas, capacidadBytes);

        cout << "\nBytes reservados: " << capacidadBytes << "\n";
        Mostrar_binario(tablero, capacidadBytes);
        cout << "Dimensiones: " << filas << " x " << columnas << "\n";

        cout << "\n1. Eliminar ficha  2. Agregar fila  3. Eliminar fila\n";
        cout << "4. Agregar columna  5. Eliminar columna  6. Salir\nOpcion: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            int fila, columna;
            cout << "Fila: ";    cin >> fila;
            cout << "Columna: "; cin >> columna;

            delete[] marcado;
            marcado = new bool[filas * columnas];

            bool exito = Eliminar_ficha_jugador(tablero, filas, columnas, capacidadBytes, fila, columna, marcado,
                                                &eliminacionesDirectas,
                                                &combinacionesTotales, &fichasTotales, &cascadasTotales,
                                                &combinacionesEstaJugada, &fichasEstaJugada, &cascadasEstaJugada,
                                                &puntuacion, true);

            if (!exito) { cout << "Jugada invalida.\n"; continue; }

        } else if (opcion == 2) {
            int posicion;
            cout << "Posicion (0 a " << filas << "): "; cin >> posicion;
            Agregar_fila(&tablero, &filas, columnas, &capacidadBytes, posicion);

            delete[] marcado;

            marcado = new bool[filas * columnas];
            Rellenar_vacios(tablero, filas, columnas, capacidadBytes);
            Procesar_cascadas(tablero, filas, columnas, capacidadBytes, marcado,
                              &combinacionesTotales, &fichasTotales, &cascadasTotales,
                              &combinacionesEstaJugada, &fichasEstaJugada, &cascadasEstaJugada,
                              &puntuacion, true);

        } else if (opcion == 3) {
            int posicion;
            cout << "Posicion (0 a " << (filas - 1) << "): "; cin >> posicion;
            Eliminar_fila(&tablero, &filas, columnas, &capacidadBytes, posicion);

        } else if (opcion == 4) {
            int posicion;
            cout << "Posicion (0 a " << columnas << "): "; cin >> posicion;
            Agregar_columna(&tablero, filas, &columnas, &capacidadBytes, posicion);

            delete[] marcado;
            marcado = new bool[filas * columnas];

            Rellenar_vacios(tablero, filas, columnas, capacidadBytes);
            Procesar_cascadas(tablero, filas, columnas, capacidadBytes, marcado,
                              &combinacionesTotales, &fichasTotales, &cascadasTotales,
                              &combinacionesEstaJugada, &fichasEstaJugada, &cascadasEstaJugada,
                              &puntuacion, true);

        } else if (opcion == 5) {
            int posicion;
            cout << "Posicion (0 a " << (columnas - 1) << "): "; cin >> posicion;
            Eliminar_columna(&tablero, filas, &columnas, &capacidadBytes, posicion);

        } else if (opcion == 6) {
            jugando = false;
            continue;

        } else {
            cout << "Opcion invalida.\n";
            continue;
        }

        cout << "\nEliminaciones: " << eliminacionesDirectas
             << " : Fichas eliminadas (total): " << fichasTotales
             << " : Combinaciones (total): " << combinacionesTotales
             << " : Combinaciones esta jugada: " << combinacionesEstaJugada
             << " : Fichas esta jugada: " << fichasEstaJugada
             << " : Cascadas esta jugada: " << cascadasEstaJugada
             << " : Puntuacion: " << puntuacion << "\n";
    }

    delete[] marcado;
    Liberar_tablero(tablero);
    cout << "\nPuntuacion final: " << puntuacion << "\n";
    return 0;
}