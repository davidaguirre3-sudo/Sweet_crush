#include "memoria.h"
#include "bitwise.h"

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

void Agregar_fila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion) {
    if (posicion < 0 || posicion > *filas) return;

    int nuevoFilas = *filas + 1;
    int bytesNuevos = Calcular_bytesnecesarios(nuevoFilas, columnas);

    unsigned char* nuevoTablero = new unsigned char[bytesNuevos];
    for (int i = 0; i < bytesNuevos; i++) nuevoTablero[i] = 0;

    for (int fOrigen = 0; fOrigen < *filas; fOrigen++) {
        int fDestino = (fOrigen < posicion) ? fOrigen : fOrigen + 1;
        for (int c = 0; c < columnas; c++) {
            int valor = Extraer_ficha(*tablero, columnas, fOrigen, c);
            Escribir_ficha(nuevoTablero, columnas, fDestino, c, valor);
        }
    }

    for (int c = 0; c < columnas; c++) {
        Escribir_ficha(nuevoTablero, columnas, posicion, c, 6);   // fila nueva, vacia
    }

    delete[] *tablero;
    *tablero = nuevoTablero;
    *filas = nuevoFilas;
    *capacidadBytes = bytesNuevos;
}

void Eliminar_fila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion) {
    if (*filas <= 1 || posicion < 0 || posicion >= *filas) return;

    for (int fOrigen = posicion + 1; fOrigen < *filas; fOrigen++) {
        int fDestino = fOrigen - 1;
        for (int c = 0; c < columnas; c++) {
            int valor = Extraer_ficha(*tablero, columnas, fOrigen, c);
            Escribir_ficha(*tablero, columnas, fDestino, c, valor);
        }
    }

    int nuevoFilas = *filas - 1;
    int bytesNecesarios = Calcular_bytesnecesarios(nuevoFilas, columnas);

    if (bytesNecesarios * 100 < *capacidadBytes * 65) {
        unsigned char* tableroCompacto = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) tableroCompacto[i] = 0;

        for (int f = 0; f < nuevoFilas; f++) {
            for (int c = 0; c < columnas; c++) {
                int valor = Extraer_ficha(*tablero, columnas, f, c);
                Escribir_ficha(tableroCompacto, columnas, f, c, valor);
            }
        }

        delete[] *tablero;
        *tablero = tableroCompacto;
        *capacidadBytes = bytesNecesarios;
    }

    *filas = nuevoFilas;
}

void Agregar_columna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion) {
    if (posicion < 0 || posicion > *columnas) return;

    int columnasViejas = *columnas;
    int columnasNuevas = columnasViejas + 1;
    int bytesNuevos = Calcular_bytesnecesarios(filas, columnasNuevas);

    unsigned char* nuevoTablero = new unsigned char[bytesNuevos];
    for (int i = 0; i < bytesNuevos; i++) nuevoTablero[i] = 0;

    for (int f = 0; f < filas; f++) {
        for (int cOrigen = 0; cOrigen < columnasViejas; cOrigen++) {
            int cDestino = (cOrigen < posicion) ? cOrigen : cOrigen + 1;
            int valor = Extraer_ficha(*tablero, columnasViejas, f, cOrigen);
            Escribir_ficha(nuevoTablero, columnasNuevas, f, cDestino, valor);
        }
        Escribir_ficha(nuevoTablero, columnasNuevas, f, posicion, 6);
    }

    delete[] *tablero;
    *tablero = nuevoTablero;
    *columnas = columnasNuevas;
    *capacidadBytes = bytesNuevos;
}

void Eliminar_columna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion) {
    if (*columnas <= 1 || posicion < 0 || posicion >= *columnas) return;

    int columnasViejas = *columnas;
    int columnasNuevas = columnasViejas - 1;
    int* temp = new int[columnasViejas];

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnasViejas; c++) {
            temp[c] = Extraer_ficha(*tablero, columnasViejas, f, c);
        }
        for (int c = 0; c < columnasViejas; c++) {
            if (c == posicion) continue;
            int cDestino = (c < posicion) ? c : c - 1;
            Escribir_ficha(*tablero, columnasNuevas, f, cDestino, temp[c]);
        }
    }
    delete[] temp;

    int bytesNecesarios = Calcular_bytesnecesarios(filas, columnasNuevas);

    if (bytesNecesarios * 100 < *capacidadBytes * 65) {
        unsigned char* tableroCompacto = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) tableroCompacto[i] = 0;

        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnasNuevas; c++) {
                int valor = Extraer_ficha(*tablero, columnasNuevas, f, c);
                Escribir_ficha(tableroCompacto, columnasNuevas, f, c, valor);
            }
        }
        delete[] *tablero;
        *tablero = tableroCompacto;
        *capacidadBytes = bytesNecesarios;
    }
    *columnas = columnasNuevas;
}
