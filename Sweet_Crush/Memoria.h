#ifndef MEMORIA_H
#define MEMORIA_H

int Calcular_bytesnecesarios(int filas, int columnas);
unsigned char* Crear_tablero(int filas, int columnas, int* bytesReservados);
void Liberar_tablero(unsigned char* tablero);

void Agregar_fila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion);
void Eliminar_fila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion);

void Agregar_columna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion);
void Eliminar_columna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion);

#endif
