#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Jugador {
    string nombre;
    int puntos;
};

int main() {
    int capacidad = 20; 
    Jugador* ranking = new Jugador[capacidad];
    int contador = 0;

    ifstream archivo("puntuaciones.txt");
    string linea;

    if (!archivo.is_open()) {
        cout << "no se pudo abrir el archivo de puntajes"<<endl;
        return 1;
    }

    while (getline(archivo, linea) && contador < capacidad) {
        
        size_t posNombre = linea.find("\"nombre\": \"");
        if (posNombre != string::npos) {
            size_t inicio = posNombre + 11;
            size_t fin = linea.find("\"", inicio);
            ranking[contador].nombre = linea.substr(inicio, fin - inicio);
        }

        size_t posPuntos = linea.find("\"puntos\": ");
        if (posPuntos != string::npos) {
            size_t inicio = posPuntos + 10;
            size_t fin = linea.find(",", inicio);
            if (fin == string::npos) fin = linea.find("}", inicio);
            
            string valorPuntos = linea.substr(inicio, fin - inicio);
            ranking[contador].puntos = stoi(valorPuntos);
        }
        contador++;
    }
    archivo.close();

    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (ranking[j].puntos < ranking[j+1].puntos) {
                Jugador temp = ranking[j];
                ranking[j] = ranking[j+1];
                ranking[j+1] = temp;
            }
        }
    }
    cout << "Top 10 mejores jugfadores!!"<<endl;
    for (int i = 0; i < contador; i++) {
        cout << i + 1 << ". " << ranking[i].nombre << " -> " << ranking[i].puntos << " puntos." << endl;
    }

    delete[] ranking;

    return 0;
}