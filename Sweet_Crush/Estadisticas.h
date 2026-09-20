#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

int Contar_marcadas(const bool* marcado, int filas, int columnas);
void Registrar_eliminacion_directa(int* eliminacionesDirectas);
void Registrar_ronda(int* combinacionesTotales, int* fichasTotales, int* puntuacion, int fichasRonda, bool esCascada);
void Registrar_cascada(int* cascadasTotales);

#endif
