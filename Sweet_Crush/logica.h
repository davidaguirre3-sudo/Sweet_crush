#ifndef LOGICA_H
#define LOGICA_H

int Generar_ficha_aleatoria();
void Rellenar_tablero(unsigned char* tablero, int filas, int columnas);

void Buscar_horizontal(const unsigned char* tablero, int filas, int columnas, bool* marcado);
void Buscar_vertical(const unsigned char* tablero, int filas, int columnas, bool* marcado);
bool Detectar_combinaciones(const unsigned char* tablero, int filas, int columnas, bool* marcado);

void Eliminar_marcadas(unsigned char* tablero, int filas, int columnas, const bool* marcado);
void Aplicar_gravedad(unsigned char* tablero, int filas, int columnas);

void Rellenar_vacios(unsigned char* tablero, int filas, int columnas);
void Procesar_cascadas(unsigned char* tablero, int filas, int columnas, bool* marcado);

#endif // LOGICA_H
