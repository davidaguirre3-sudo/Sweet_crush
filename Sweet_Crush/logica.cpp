#include <cstdlib>
#include "logica.h"
#include "bitwise.h"

int Generar_ficha_aleatoria() {
    return rand() % 6;   // 0 a 5: los 6 tipos de ficha jugables
}

void Rellenar_tablero(unsigned char* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int valor = Generar_ficha_aleatoria();
            Escribir_ficha(tablero, columnas, f, c, valor);
        }
    }
}

void Buscar_horizontal(const unsigned char* tablero, int filas, int columnas, bool* marcado) {
    for (int f = 0; f < filas; f++) {
        int c = 0;
        while (c < columnas) {
            int valorActual = Extraer_ficha(tablero, columnas, f, c);

            if (valorActual >= 6) {   // vacio o reservado: no cuenta
                c++;
                continue;
            }

            int inicio = c;
            while (c < columnas && Extraer_ficha(tablero, columnas, f, c) == valorActual) {
                c++;
            }
            int largo = c - inicio;

            if (largo >= 3) {
                for (int k = inicio; k < c; k++) {
                    marcado[f * columnas + k] = true;
                }
            }
        }
    }
}

void Buscar_vertical(const unsigned char* tablero, int filas, int columnas, bool* marcado) {
    for (int c = 0; c < columnas; c++) {
        int f = 0;
        while (f < filas) {
            int valorActual = Extraer_ficha(tablero, columnas, f, c);

            if (valorActual >= 6) {
                f++;
                continue;
            }

            int inicio = f;
            while (f < filas && Extraer_ficha(tablero, columnas, f, c) == valorActual) {
                f++;
            }
            int largo = f - inicio;

            if (largo >= 3) {
                for (int k = inicio; k < f; k++) {
                    marcado[k * columnas + c] = true;
                }
            }
        }
    }
}

bool Detectar_combinaciones(const unsigned char* tablero, int filas, int columnas, bool* marcado) {
    for (int i = 0; i < filas * columnas; i++) {
        marcado[i] = false;
    }

    Buscar_horizontal(tablero, filas, columnas, marcado);
    Buscar_vertical(tablero, filas, columnas, marcado);

    for (int i = 0; i < filas * columnas; i++) {
        if (marcado[i]) return true;
    }
    return false;
}