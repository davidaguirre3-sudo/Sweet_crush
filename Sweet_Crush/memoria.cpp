#include "memoria.h"
#include "bitwise.h"

int Calcular_bytesnecesarios(int filas, int columnas) {
    int bitsNecesarios = filas * columnas * 3;
    return (bitsNecesarios + 7) / 8;
}

unsigned char* Crear_tablero(int filas, int columnas, int* bytesReservados) {
    int bytes = Calcular_bytesnecesarios(filas, columnas);
    unsigned char* tablero = new unsigned char[bytes];
    for (int i = 0; i < bytes; i++) tablero[i] = 0;
    *bytesReservados = bytes;
    return tablero;
}

void Liberar_tablero(unsigned char* tablero) {
    delete[] tablero;
}

void Agregar_fila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion) {
    if (posicion < 0 || posicion > *filas) return;

    int filasViejas = *filas;
    int offsetViejo = Calcular_offset_inicial(filasViejas, columnas, *capacidadBytes);

    int nuevoFilas = filasViejas + 1;
    int bytesNuevos = Calcular_bytesnecesarios(nuevoFilas, columnas);
    int offsetNuevo = Calcular_offset_inicial(nuevoFilas, columnas, bytesNuevos);

    unsigned char* nuevoTablero = new unsigned char[bytesNuevos];
    for (int i = 0; i < bytesNuevos; i++) nuevoTablero[i] = 0;

    for (int fOrigen = 0; fOrigen < filasViejas; fOrigen++) {
        int fDestino = (fOrigen < posicion) ? fOrigen : fOrigen + 1;
        for (int c = 0; c < columnas; c++) {
            int valor = Extraer_ficha(*tablero, columnas, fOrigen, c, offsetViejo);
            Escribir_ficha(nuevoTablero, columnas, fDestino, c, valor, offsetNuevo);
        }
    }
    for (int c = 0; c < columnas; c++) {
        Escribir_ficha(nuevoTablero, columnas, posicion, c, 6, offsetNuevo);
    }

    delete[] *tablero;
    *tablero = nuevoTablero;
    *filas = nuevoFilas;
    *capacidadBytes = bytesNuevos;
}

void Eliminar_fila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion) {
    if (*filas <= 1 || posicion < 0 || posicion >= *filas) return;

    int filasViejas = *filas;
    int offsetViejo = Calcular_offset_inicial(filasViejas, columnas, *capacidadBytes);
    int nuevoFilas = filasViejas - 1;

    int* temp = new int[nuevoFilas * columnas];
    int idx = 0;
    for (int f = 0; f < filasViejas; f++) {
        if (f == posicion) continue;
        for (int c = 0; c < columnas; c++) {
            temp[idx] = Extraer_ficha(*tablero, columnas, f, c, offsetViejo);
            idx++;
        }
    }

    int bytesNecesarios = Calcular_bytesnecesarios(nuevoFilas, columnas);

    if (bytesNecesarios * 100 < *capacidadBytes * 65) {
        unsigned char* tableroCompacto = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) tableroCompacto[i] = 0;
        int offsetNuevo = Calcular_offset_inicial(nuevoFilas, columnas, bytesNecesarios);

        idx = 0;
        for (int f = 0; f < nuevoFilas; f++)
            for (int c = 0; c < columnas; c++) {
                Escribir_ficha(tableroCompacto, columnas, f, c, temp[idx], offsetNuevo);
                idx++;
            }

        delete[] *tablero;
        *tablero = tableroCompacto;
        *capacidadBytes = bytesNecesarios;
    } else {
        int offsetNuevo = Calcular_offset_inicial(nuevoFilas, columnas, *capacidadBytes);
        idx = 0;
        for (int f = 0; f < nuevoFilas; f++)
            for (int c = 0; c < columnas; c++) {
                Escribir_ficha(*tablero, columnas, f, c, temp[idx], offsetNuevo);
                idx++;
            }
    }

    delete[] temp;
    *filas = nuevoFilas;
}

void Agregar_columna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion) {
    if (posicion < 0 || posicion > *columnas) return;

    int columnasViejas = *columnas;
    int offsetViejo = Calcular_offset_inicial(filas, columnasViejas, *capacidadBytes);

    int columnasNuevas = columnasViejas + 1;
    int bytesNuevos = Calcular_bytesnecesarios(filas, columnasNuevas);
    int offsetNuevo = Calcular_offset_inicial(filas, columnasNuevas, bytesNuevos);

    unsigned char* nuevoTablero = new unsigned char[bytesNuevos];
    for (int i = 0; i < bytesNuevos; i++) nuevoTablero[i] = 0;

    for (int f = 0; f < filas; f++) {
        for (int cOrigen = 0; cOrigen < columnasViejas; cOrigen++) {
            int cDestino = (cOrigen < posicion) ? cOrigen : cOrigen + 1;
            int valor = Extraer_ficha(*tablero, columnasViejas, f, cOrigen, offsetViejo);
            Escribir_ficha(nuevoTablero, columnasNuevas, f, cDestino, valor, offsetNuevo);
        }
        Escribir_ficha(nuevoTablero, columnasNuevas, f, posicion, 6, offsetNuevo);
    }

    delete[] *tablero;
    *tablero = nuevoTablero;
    *columnas = columnasNuevas;
    *capacidadBytes = bytesNuevos;
}

void Eliminar_columna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion) {
    if (*columnas <= 1 || posicion < 0 || posicion >= *columnas) return;

    int columnasViejas = *columnas;
    int offsetViejo = Calcular_offset_inicial(filas, columnasViejas, *capacidadBytes);
    int columnasNuevas = columnasViejas - 1;

    int* temp = new int[filas * columnasNuevas];
    int idx = 0;
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnasViejas; c++) {
            if (c == posicion) continue;
            temp[idx] = Extraer_ficha(*tablero, columnasViejas, f, c, offsetViejo);
            idx++;
        }
    }

    int bytesNecesarios = Calcular_bytesnecesarios(filas, columnasNuevas);

    if (bytesNecesarios * 100 < *capacidadBytes * 65) {
        unsigned char* tableroCompacto = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) tableroCompacto[i] = 0;
        int offsetNuevo = Calcular_offset_inicial(filas, columnasNuevas, bytesNecesarios);

        idx = 0;
        for (int f = 0; f < filas; f++)
            for (int c = 0; c < columnasNuevas; c++) {
                Escribir_ficha(tableroCompacto, columnasNuevas, f, c, temp[idx], offsetNuevo);
                idx++;
            }

        delete[] *tablero;
        *tablero = tableroCompacto;
        *capacidadBytes = bytesNecesarios;
    } else {
        int offsetNuevo = Calcular_offset_inicial(filas, columnasNuevas, *capacidadBytes);
        idx = 0;
        for (int f = 0; f < filas; f++)
            for (int c = 0; c < columnasNuevas; c++) {
                Escribir_ficha(*tablero, columnasNuevas, f, c, temp[idx], offsetNuevo);
                idx++;
            }
    }

    delete[] temp;
    *columnas = columnasNuevas;
}
