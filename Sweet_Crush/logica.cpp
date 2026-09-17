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

void Eliminar_marcadas(unsigned char* tablero, int filas, int columnas, const bool* marcado) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int indice = f * columnas + c;
            if (marcado[indice]) {
                Escribir_ficha(tablero, columnas, f, c, 6);   // 6 = vacio
            }
        }
    }
}

void Aplicar_gravedad(unsigned char* tablero, int filas, int columnas) {
    for (int c = 0; c < columnas; c++) {
        int filaEscritura = filas - 1;

        for (int f = filas - 1; f >= 0; f--) {
            int valor = Extraer_ficha(tablero, columnas, f, c);

            if (valor != 6) {
                if (f != filaEscritura) {
                    Escribir_ficha(tablero, columnas, filaEscritura, c, valor);
                    Escribir_ficha(tablero, columnas, f, c, 6);
                }
                filaEscritura--;
            }
        }
    }
}

void Rellenar_vacios(unsigned char* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int valor = Extraer_ficha(tablero, columnas, f, c);
            if (valor == 6) {
                int nuevo = Generar_ficha_aleatoria();
                Escribir_ficha(tablero, columnas, f, c, nuevo);
            }
        }
    }
}

void Procesar_cascadas(unsigned char* tablero, int filas, int columnas, bool* marcado) {
    bool hayCombinacion = Detectar_combinaciones(tablero, filas, columnas, marcado);

    while (hayCombinacion) {
        Eliminar_marcadas(tablero, filas, columnas, marcado);
        Aplicar_gravedad(tablero, filas, columnas);
        Rellenar_vacios(tablero, filas, columnas);

        hayCombinacion = Detectar_combinaciones(tablero, filas, columnas, marcado);
    }
}