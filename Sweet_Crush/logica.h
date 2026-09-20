#ifndef LOGICA_H
#define LOGICA_H

int Generar_ficha_aleatoria();
void Rellenar_tablero(unsigned char* tablero, int filas, int columnas, int capacidadBytes);
void Rellenar_vacios(unsigned char* tablero, int filas, int columnas, int capacidadBytes);

void Buscar_horizontal(const unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado);
void Buscar_vertical(const unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado);
bool Detectar_combinaciones(const unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado);

void Eliminar_marcadas(unsigned char* tablero, int filas, int columnas, int capacidadBytes, const bool* marcado);
void Aplicar_gravedad(unsigned char* tablero, int filas, int columnas, int capacidadBytes);

void Procesar_cascadas(unsigned char* tablero, int filas, int columnas, int capacidadBytes, bool* marcado,
                       int* combinacionesTotales, int* fichasTotales, int* cascadasTotales,
                       int* combinacionesEstaJugada, int* fichasEstaJugada, int* cascadasEstaJugada,
                       int* puntuacion, bool mostrarProgreso);

bool Eliminar_ficha_jugador(unsigned char* tablero, int filas, int columnas, int capacidadBytes, int fila, int columna, bool* marcado,
                            int* eliminacionesDirectas,int* combinacionesTotales, int* fichasTotales, int* cascadasTotales,
                            int* combinacionesEstaJugada, int* fichasEstaJugada, int* cascadasEstaJugada,
                            int* puntuacion, bool mostrarProgreso);

#endif