#ifndef MEMORIA_H
#define MEMORIA_H

int Calcular_bytesnecesarios(int filas, int columnas);
unsigned char* Crear_tablero(int filas, int columnas, int* bytesReservados);
void Liberar_tablero(unsigned char* tablero);

#endif
