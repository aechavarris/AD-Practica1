#include <iostream>
#include "lib/graficos/Vertice.h"
#include "lib/graficos/Arista.h"
#include "lib/graficos/Grafo.h"
using namespace std;

int main(int argv,char* argc[]) {

    Grafo prueba = Grafo();

    prueba.addArista(Arista(Vertice(0),Vertice(1)));
    prueba.addArista(Arista(Vertice(1),Vertice(3)));
    prueba.addArista(Arista(Vertice(3),Vertice(2)));
    prueba.addArista(Arista(Vertice(3),Vertice(0)));
    prueba.addArista(Arista(Vertice(0),Vertice(2)));
    prueba.addArista(Arista(Vertice(3),Vertice(4)));
    prueba.addArista(Arista(Vertice(4),Vertice(2)));

    cout << "Grafo: "<< prueba.toString() << endl;
    cout << "Minimo grado: "<<prueba.minGrado() << endl;
    cout << "Maximo grado: "<<prueba.maxGrado() << endl;
    return 0;
}