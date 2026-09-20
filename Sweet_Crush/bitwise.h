#ifndef BITWISE_H
#define BITWISE_H

int Calcular_offset_inicial(int filas, int columnas, int capacidadBytes);
int Extraer_ficha(const unsigned char* tablero, int columnas, int fila, int columna, int offsetInicial);
void Escribir_ficha(unsigned char* tablero, int columnas, int fila, int columna, int valor, int offsetInicial);

#endif