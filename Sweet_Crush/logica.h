#ifndef LOGICA_H
#define LOGICA_H

int Generar_ficha_aleatoria();
void Rellenar_tablero(unsigned char* tablero, int filas, int columnas);

void Buscar_horizontal(const unsigned char* tablero, int filas, int columnas, bool* marcado);
void Buscar_vertical(const unsigned char* tablero, int filas, int columnas, bool* marcado);
bool Detectar_combinaciones(const unsigned char* tablero, int filas, int columnas, bool* marcado);

#endif // LOGICA_H
