#include "Interfaz.h"
#include <iostream>
#include "bitwise.h"

using namespace std;

char Convertir_caracter(int valorFicha) {
    switch (valorFicha) {
    case 0: return 'A';
    case 1: return 'B';
    case 2: return 'C';
    case 3: return 'D';
    case 4: return 'E';
    case 5: return 'F';
    case 6: return '.';
    case 7: return '*';
    default: return '?';
    }
}

void Mostrar_tablero(const unsigned char* tablero, int filas, int columnas, int capacidadBytes) {
    int offsetInicial = Calcular_offset_inicial(filas, columnas, capacidadBytes);

    cout << "    ";
    for (int c = 0; c < columnas; c++) {
        if (c < 10) cout << "  " << c;
        else cout << " " << c;
    }
    cout << "\n";

    for (int f = 0; f < filas; f++) {
        if (f < 10) cout << "  " << f << " ";
        else cout << " " << f << " ";

        for (int c = 0; c < columnas; c++) {
            int valor = Extraer_ficha(tablero, columnas, f, c, offsetInicial);
            cout << "  " << Convertir_caracter(valor);
        }
        cout << "\n";
    }
}

void Mostrar_binario(const unsigned char* tablero, int bytesReservados) {
    for (int i = 0; i < bytesReservados; i++) {
        for (int posicionHardware = 7; posicionHardware >= 0; posicionHardware--) {
            unsigned char mascara = 1 << posicionHardware;
            cout << ((tablero[i] & mascara) ? '1' : '0');
        }
        cout << " ";
    }
    cout << "\n";
}