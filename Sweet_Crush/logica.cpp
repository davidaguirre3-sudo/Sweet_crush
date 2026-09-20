#include <iostream>
#include <cstdlib>
#include "logica.h"
#include "bitwise.h"
#include "estadisticas.h"
#include "interfaz.h"

using namespace std;

int Generar_ficha_aleatoria() {
    return rand() % 6;
}

void Rellenar_tablero(unsigned char* tablero, int filas, int columnas, int capacidadBytes) {
    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int valor = Generar_ficha_aleatoria();
            Escribir_ficha(tablero, columnas, f, c, valor, offsetInicial);
        }
    }
}

void Rellenar_vacios(unsigned char* tablero, int filas, int columnas, int capacidadBytes) {
    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int valor = Extraer_ficha(tablero, columnas, f, c, offsetInicial);
            if (valor == 6) {
                int nuevo = Generar_ficha_aleatoria();
                Escribir_ficha(tablero, columnas, f, c, nuevo, offsetInicial);
            }
        }
    }
}

void Buscar_horizontal(const unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado) {
    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);

    for (int f = 0; f < filas; f++) {
        int c = 0;
        while (c < columnas) {
            int valorActual = Extraer_ficha(tablero, columnas, f, c, offsetInicial);

            if (valorActual >= 6) {
                c++;
                continue;
            }

            int inicio = c;
            while (c < columnas && Extraer_ficha(tablero, columnas, f, c, offsetInicial) == valorActual) {
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

void Buscar_vertical(const unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado) {
    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);

    for (int c = 0; c < columnas; c++) {
        int f = 0;
        while (f < filas) {
            int valorActual = Extraer_ficha(tablero, columnas, f, c, offsetInicial);

            if (valorActual >= 6) {
                f++;
                continue;
            }

            int inicio = f;
            while (f < filas && Extraer_ficha(tablero, columnas, f, c, offsetInicial) == valorActual) {
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

bool Detectar_combinaciones(const unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado) {
    for (int i = 0; i < filas * columnas; i++) {
        marcado[i] = false;
    }

    Buscar_horizontal(tablero, filas, columnas, capacidadBytes, marcado);
    Buscar_vertical(tablero, filas, columnas, capacidadBytes, marcado);

    for (int i = 0; i < filas * columnas; i++) {
        if (marcado[i]) return true;
    }
    return false;
}

void Eliminar_marcadas(unsigned char* tablero, int filas, int columnas, int capacidadBytes, const bool* marcado) {
    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int indice = f * columnas + c;
            if (marcado[indice]) {
                Escribir_ficha(tablero, columnas, f, c, 6, offsetInicial);
            }
        }
    }
}

void Aplicar_gravedad(unsigned char* tablero, int filas, int columnas, int capacidadBytes) {
    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);

    for (int c = 0; c < columnas; c++) {
        int filaEscritura = filas - 1;

        for (int f = filas - 1; f >= 0; f--) {
            int valor = Extraer_ficha(tablero, columnas, f, c, offsetInicial);

            if (valor != 6) {
                if (f != filaEscritura) {
                    Escribir_ficha(tablero, columnas, filaEscritura, c, valor, offsetInicial);
                    Escribir_ficha(tablero, columnas, f, c, 6, offsetInicial);
                }
                filaEscritura--;
            }
        }
    }
}

void Procesar_cascadas(unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado,
                       int* combinacionesTotales, int* fichasTotales, int* cascadasTotales,
                       int* combinacionesEstaJugada, int* fichasEstaJugada, int* cascadasEstaJugada,
                       int* puntuacion, bool mostrarProgreso) {

    *combinacionesEstaJugada = 0;
    *fichasEstaJugada = 0;
    *cascadasEstaJugada = 0;

    bool hayCombinacion = Detectar_combinaciones(tablero, filas, columnas, capacidadBytes, marcado);
    int ronda = 1;

    while (hayCombinacion) {
        int fichasRonda = Contar_marcadas(marcado, filas, columnas);
        bool esCascada = (ronda >= 2);

        Registrar_ronda(combinacionesTotales, fichasTotales, puntuacion, fichasRonda, esCascada);
        (*combinacionesEstaJugada)++;
        *fichasEstaJugada += fichasRonda;

        if (esCascada) {
            Registrar_cascada(cascadasTotales);
            (*cascadasEstaJugada)++;
        }

        Eliminar_marcadas(tablero, filas, columnas, capacidadBytes, marcado);
        Aplicar_gravedad(tablero, filas, columnas, capacidadBytes);
        Rellenar_vacios(tablero, filas, columnas, capacidadBytes);

        if (mostrarProgreso) {
            cout << "\n-- Ronda " << ronda << (esCascada ? " (cascada)" : "") << ": "
                 << fichasRonda << " fichas eliminadas --\n";
            Mostrar_tablero(tablero, filas, columnas, capacidadBytes);
        }

        hayCombinacion = Detectar_combinaciones(tablero, filas, columnas, capacidadBytes, marcado);
        ronda++;
    }
}

bool Eliminar_ficha_jugador(unsigned char* tablero, int filas, int columnas, int capacidadBytes, int fila, int columna, bool* marcado,
                            int* eliminacionesDirectas, int* combinacionesTotales, int* fichasTotales, int* cascadasTotales,
                            int* combinacionesEstaJugada, int* fichasEstaJugada, int* cascadasEstaJugada,
                            int* puntuacion, bool mostrarProgreso) {

    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return false;
    }

    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);
    int valorActual = Extraer_ficha(tablero, columnas, fila, columna, offsetInicial);
    if (valorActual == 6) {
        return false;
    }

    for (int i = 0; i < filas * columnas; i++) {
        marcado[i] = false;
    }
    marcado[fila * columnas + columna] = true;

    Eliminar_marcadas(tablero, filas, columnas, capacidadBytes, marcado);
    Aplicar_gravedad(tablero, filas, columnas, capacidadBytes);
    Rellenar_vacios(tablero, filas, columnas, capacidadBytes);

    Registrar_eliminacion_directa(eliminacionesDirectas);
    Procesar_cascadas(tablero, filas, columnas, capacidadBytes, marcado,combinacionesTotales, fichasTotales, cascadasTotales,
                      combinacionesEstaJugada, fichasEstaJugada, cascadasEstaJugada,puntuacion, mostrarProgreso);

    *fichasTotales += 1;
    *fichasEstaJugada += 1;

    return true;
}