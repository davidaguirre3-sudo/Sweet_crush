#include "bitwise.h"

int Calcular_offset_inicial(int filas, int columnas, int capacidadBytes) {
    int bitsValidos = filas * columnas * 3;
    int bitsTotales = capacidadBytes * 8;
    return bitsTotales - bitsValidos;
}

int Extraer_ficha(const unsigned char* tablero, int columnas, int fila, int columna, int offsetInicial) {
    int indice = fila * columnas + columna;
    int bitInicio = offsetInicial + indice * 3;

    int valor = 0;
    for (int k = 0; k < 3; k++) {
        int p = bitInicio + k;
        int byteIndex = p / 8;
        int posicionHardware = 7 - (p % 8);

        unsigned char mascara = 1 << posicionHardware;
        int bit = (tablero[byteIndex] & mascara) ? 1 : 0;
        valor = (valor << 1) | bit;
    }
    return valor;
}

void Escribir_ficha(unsigned char* tablero, int columnas, int fila, int columna, int valor, int offsetInicial) {
    int indice = fila * columnas + columna;
    int bitInicio = offsetInicial + indice * 3;

    for (int k = 0; k < 3; k++) {
        int p = bitInicio + k;
        int byteIndex = p / 8;
        int posicionHardware = 7 - (p % 8);

        int bit = (valor >> (2 - k)) & 1;
        unsigned char mascara = 1 << posicionHardware;

        if (bit) tablero[byteIndex] = tablero[byteIndex] | mascara;
        else tablero[byteIndex] = tablero[byteIndex] & (~mascara);
    }
}