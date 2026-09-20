#include "estadisticas.h"

int Contar_marcadas(const bool* marcado, int filas, int columnas) {
    int total = 0;
    for (int i = 0; i < filas * columnas; i++) {
        if (marcado[i])
            total++;
    }
    return total;
}

void Registrar_eliminacion_directa(int* eliminacionesDirectas) {
    (*eliminacionesDirectas)++;   
}

void Registrar_ronda(int* combinacionesTotales, int* fichasTotales, int* puntuacion, int fichasRonda, bool esCascada) {
    (*combinacionesTotales)++;
    *fichasTotales += fichasRonda;

    int puntos = fichasRonda * 10;
    if (esCascada) {
        puntos *= 2;
    }
    *puntuacion += puntos;
}

void Registrar_cascada(int* cascadasTotales) {
    (*cascadasTotales)++;
}