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

using namespace std;
struct OrderNodo
{
    bool operator()(Vertice v1,Vertice v2) const{
            if(v1.grado == v2.grado ){
                return v1.id <= v2.id; 
            }else{
                return v1.grado > v2.grado;
            }
        }
};

int info_fichero(string fichero) {
    fstream my_file;
    my_file.open(fichero, ios::in);

    if(my_file.is_open()) { 
        char *linea = (char*)malloc(sizeof(char[1000]));
        my_file.getline(linea, 1000, '\n');
        my_file.close();
        return atoi(linea);
    }

    cout << "No se ha podido abrir el fichero " << fichero << endl;
    exit(1);
}

void get_weight(int start,int end,string fichero, int dim, Grafo* grafo) {
    fstream my_file;
    my_file.open(fichero, ios::in);
    const int dim2 = dim * 2 + 1;
    // Declaración de variables utilizadas
    char *linea = (char*)malloc(sizeof(char[dim2]));
    char *tmp = (char*)malloc(sizeof(char[dim2]));
    set<Vertice,OrderNodo> grados;
    int i = start, j = 0;
    float tmp_f;
    int count = start;
    if(my_file.is_open()) { 
        my_file.seekg(start * dim, std::ios::cur);
        
        while(!my_file.eof() && count <= end) { 
            //cout << endl; 
            int grado = 0;
            my_file.getline(linea, dim2, '\n');
            //cout << linea <<endl;
            count++;
            //cout << count/end << " %" << endl;
            printf ("%f", (float)count/(float)end);
            cout <<" %" << endl;
            tmp = strtok(linea," ");

            while (tmp != NULL) {
                tmp_f = atoi(tmp);
                //cout << tmp_f << " ";
                
                if(tmp_f == 1) {
                    //cout << "Introduce arista: "<<arista.toString()<<endl;
                    //grafo->addArista(arista);
                    grado ++;
                    grafo->matrix[i-1][j] = true;
                }else{
                    grafo->matrix[i-1][j] = false;
                }
                j++;
                tmp = strtok (NULL, " ");
            }
            
            Vertice nuevo =Vertice(i-1);
            nuevo.grado = grado;
            cout << "Inserto vertice " << nuevo.id << " de grado " << grado << endl;
            grados.insert(nuevo);
            j = 0;
            i++;
        }
    }
    my_file.close();
    cout <<"..."<< endl;
}

int main(int argv, char* argc[]) {
    int dim = info_fichero(argc[1]);
    Grafo* prueba = new Grafo(dim);

    
    // The info to use thread has been taken from https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php
    int nThreadsSupported = (int)std::thread::hardware_concurrency();
    vector<thread> threads = vector<thread>();

    long int start = 0;
    if(dim <= nThreadsSupported){

        cout << "Reading input matrix..." << endl;
        long int end = start +1 ;
        for (int i = 0; i < nThreadsSupported && start != end; i++)
        {   
            cout << "Start " << start << " end " << end <<endl;
            threads.push_back(thread(get_weight, start, end, argc[1], dim, ref(prueba)));
            start = end;
            end = start +1 ;
        }
        cout << "Start " << start << " end " << end <<endl;
        for (int i = 0; i < threads.size(); i++)
        {
            threads.at(i).join();
        }
    }else{
        get_weight(0, dim, argc[1], dim, prueba);
        // long int end = dim / nThreadsSupported;
        
        // cout << "Reading input matrix..." << endl;
        // cout << nThreadsSupported <<" cores" << endl;
        
        // for (int i = 0; i < nThreadsSupported; i++)
        // {   
        //     cout << "Start " << start << " end " << end <<endl;
        //     threads.push_back(thread(get_weight, start, end, argc[1], dim, ref(prueba)));
        //     start = end;
        //     end = (i == nThreadsSupported - 2) ? dim : end + dim / nThreadsSupported;
        // }
        // cout << "Start " << start << " end " << end <<endl;
        // for (int i = 0; i < threads.size(); i++)
        // {
        //     threads.at(i).join();
        // }
    }
    Algoritmos al = Algoritmos();
    for(int i = 0; i < prueba->nVertices; i++){
        for(int j = 0; j < prueba->nVertices; j++){
            if(prueba->matrix[i][j]){
                cout << "1 ";
            }else if (!prueba->matrix[i][j]){
                cout << "0 ";
            }else{
                cout << "f ";
            }
        }
        cout << endl;
    }
    //Aproximacion spanning tree recorrido en profundidad
    cout << "Aplicando Spanning-tree profundida: " <<endl;
    auto vertices = al.spanningTreeProfundidad(*prueba);
    cout << "Vertices seleccionados" << endl;
    for(int n = 0; n < vertices.size(); n++){
        cout << vertices.at(n).id <<" ";
    }
    cout << endl;

    //Aproximacion spanning tree recorrido en anchura
    cout << "\nAplicando Spanning-tree anchura: " <<endl;
    vertices = al.spanningTreeAnchura(*prueba);
    cout << "Vertices seleccionados" << endl;
    for(int n = 0; n < vertices.size(); n++){
        cout << vertices.at(n).id <<" ";
    }
    cout << endl;  

    //Aproximacion spanning tree recorrido en anchura
    cout << "\nAplicando Greddy-algorithm: " <<endl;
    vertices = al.greedyAlgorithm(*prueba);
    cout << "Vertices seleccionados" << endl;
    for(int n = 0; n < vertices.size(); n++){
        cout << vertices.at(n).id <<" ";
    }
    cout << endl;  

    cout << "Entrada: " << argc[1] << endl;
    cout << "Grafo de " << dim << " vertices" << endl;
    return 0;
}
