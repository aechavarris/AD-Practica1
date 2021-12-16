#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <set>
#include "lib/grafos/vertice/Vertice.h"
#include "lib/grafos/arista/Arista.h"
#include "lib/grafos/grafo/Grafo.h"
#include "lib/algoritmos/Algoritmos.h"
#include "lib/progressBar/ProgressBar.hpp"
using namespace std;

int info_fichero(string fichero) {
    fstream my_file;
    my_file.open(fichero, ios::in);

    if (my_file.is_open()) { 
        char *linea = (char*)malloc(sizeof(char[1000]));
        my_file.getline(linea, 1000, '\n');
        my_file.close();
        return atoi(linea);
    }

    cout << "No se ha podido abrir el fichero " << fichero << endl;
    exit(1);
}

void get_weight(string fichero, int dim, Grafo* grafo) {
    fstream my_file;
    my_file.open(fichero, ios::in);
    cout << "Leyendo matriz de entrada: \n";
    // Declaración de variables utilizadas
    const int dim2 = dim * 2 + 1;
    char *linea = (char*) malloc(sizeof(char[dim2]));
    char *tmp = (char*) malloc(sizeof(char[dim2]));
    set<Vertice, Grafo::OrderNodo> grados;
    int i = 0, j = 0;
    float tmp_f;
    int count = 0;
    const int limit = dim ;
    progresscpp::ProgressBar progressBar(limit, 70);
    if(my_file.is_open()) { 
        my_file.getline(linea, dim2, '\n');
        
        while(!my_file.eof() ) { 
            //cout << endl; 
            int grado = 0;
            my_file.getline(linea, dim2, '\n');
            //cout << linea <<endl;
            //printf ("%f", (float)count/(float)dim * 100) ;
            
            tmp = strtok(linea," ");

            while (tmp != NULL) {
                
                tmp_f = atoi(tmp);
                //cout << tmp_f << " ";
                
                if(tmp_f == 1) {
                    //cout << "Introduce arista: "<<arista.toString()<<endl;
                    //grafo->addArista(arista);
                    grado ++;
                    grafo->matrix[i][j] = true;
                }
                j++;
                tmp = strtok (NULL, " ");
            }

            if (grado != 0) {
                Vertice nuevo = Vertice(i);
                nuevo.grado = grado;
                //cout << "Inserto vertice " << nuevo.id << " de grado " << grado << endl;
                grados.insert(nuevo);
                // for(auto i = grados.begin(); i != grados.end(); i++){
                //     cout << i->grado << " " << i->id << endl;
                // }
            }
            j = 0;
            i++;
            ++progressBar;
            progressBar.display();
        }
        
    }
    my_file.close();
    progressBar.done();
    grafo->grados = grados;
}

int main(int argv, char* argc[]) {
    int dim = info_fichero(argc[1]);
    Grafo* prueba = new Grafo(dim);

    int nThreadsSupported = (int) std::thread::hardware_concurrency();
    vector<thread> threads = vector<thread>();

    get_weight(argc[1], dim, prueba);

    Algoritmos al = Algoritmos();
    // for (int i = 0; i < prueba->nVertices; i++) {
    //     for (int j = 0; j < prueba->nVertices; j++) {
    //         if (prueba->matrix[i][j]) {
    //             cout << "1 ";
    //         } else if (!prueba->matrix[i][j]) {
    //             cout << "0 ";
    //         } else {
    //             cout << "f ";
    //         }
    //     }
    //     cout << endl;
    // }

    //Aproximacion spanning tree recorrido en profundidad
    cout << "Aplicando Spanning-tree profundida: " <<endl;
    auto vertices = al.spanningTreeProfundidad(*prueba);
    cout << "Vertices seleccionados: " << vertices.size() << endl;
    for (int n = 0; n < vertices.size(); n++) {
        cout << vertices.at(n).id <<" ";
    }
    cout << endl;

    //Aproximacion spanning tree recorrido en anchura
    cout << "\nAplicando Spanning-tree anchura: " <<endl;
    vertices = al.spanningTreeAnchura(*prueba);
    cout << "Vertices seleccionados: " <<vertices.size() << endl;
    for (int n = 0; n < vertices.size(); n++) {
        cout << vertices.at(n).id <<" ";
    }
    cout << endl;  

    //Aproximacion spanning tree recorrido en anchura
    cout << "\nAplicando Greddy-algorithm: " <<endl;
    vertices = al.greedyAlgorithm(*prueba);
    cout << "Vertices seleccionados: " << vertices.size() << endl;
    for (int n = 0; n < vertices.size(); n++) {
        cout << vertices.at(n).id <<" ";
    }
    cout << endl;  

    cout << "Entrada: " << argc[1] << endl;
    cout << "Grafo de " << dim << " vertices" << endl;
    return 0;
}
