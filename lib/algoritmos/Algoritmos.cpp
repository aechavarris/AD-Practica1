/*****************************************************************
 * File:    Algoritmos.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Algoritmos
 *****************************************************************/

#pragma once

#include "Algoritmos.h"

Algoritmos::Algoritmos(){};


void Algoritmos::checkVertices(Grafo grafo,int* minVertices,bool* verticesCogidos,vector<Vertice> *vertices,vector<Vertice> *verticesFinal){
    bool check = true;
    for (int i = 0; i < grafo.nVertices; i++) {
        if (!verticesCogidos) check = false;
    }
   
    if (vertices->size()<= *minVertices && check) {
        *minVertices = vertices->size();
        verticesFinal->clear();
        for(auto i : *vertices) verticesFinal->push_back(i);
    }
    vertices->clear();
}

vector<Vertice> Algoritmos::spanningTreeProfundidad(Grafo grafo){
    vector<Vertice>* vertices = new vector<Vertice>();
    vector<Vertice>* verticesFinal = new vector<Vertice>();
    bool* verticesCogidos = new bool[grafo.nVertices];
    bool end = false;
    const int limit = grafo.nVertices ;
    progresscpp::ProgressBar progressBar(limit, 70);
    for (int i = 0; i < grafo.nVertices; i++) {
        verticesCogidos[i] = false;
    }
    int* minVertices = new int;
    *minVertices = grafo.nVertices+1;
    Vertice maxGrado = grafo.maxGrado();
    
    cout << "Nodo raiz " << maxGrado.id <<" : ";
    recorridoProfundidad(grafo,maxGrado.id,verticesCogidos,vertices);   
    for(int i = 0; i < grafo.nVertices; i++){
        verticesCogidos[i] = false;
    }
    for(int i = 0; i < vertices->size(); i++){
        cout << vertices->at(i).id << " ";
    }
    cout << endl;
    checkVertices(grafo,minVertices,verticesCogidos,vertices,verticesFinal);
    return *verticesFinal;
}

bool Algoritmos::recorridoProfundidad(Grafo &grafo, int origen, bool* verticesCogidos,vector<Vertice> *vertices){
    bool hoja = true;
    for(int i = 0; i < grafo.nVertices; i++){
        if(grafo.matrix[origen][i] && !verticesCogidos[i]){
            hoja = false;
        }
    }

    if(hoja) return true;
    vertices->push_back(Vertice(origen));
    for(int i = 0; i < grafo.nVertices; i++){
        //cout << "Inspecciono " << origen <<" "<< i <<endl;
        if(grafo.matrix[origen][i] && !verticesCogidos[i] && i != origen){
            verticesCogidos[origen]=true;
            if(!recorridoProfundidad(grafo, i, verticesCogidos, vertices)){
                verticesCogidos[origen]=false;
                //cout << "Selecciono arista (" << origen << "," << i << ")" << endl; 
                verticesCogidos[i]=true;
            }
            
        }
    }
    return false;
}

vector<Vertice> Algoritmos::spanningTreeAnchura(Grafo grafo){
    vector<Vertice>* vertices = new vector<Vertice>();
    vector<Vertice>* verticesFinal = new vector<Vertice>();
    bool* verticesCogidos = new bool[grafo.nVertices];
    for (int i = 0; i < grafo.nVertices; i++) verticesCogidos[i] = false;

    bool* verticesRecorridos = new bool[grafo.nVertices];
    for(int i = 0; i < grafo.nVertices; i++) verticesRecorridos[i] = false;

    int* minVertices = new int;
    bool** arbol;
    arbol = new bool*[grafo.nVertices];
    for (int i = 0; i < grafo.nVertices; i++) {
        arbol[i] = new bool[grafo.nVertices];
        for(int j = 0; j < grafo.nVertices; j++){
            arbol[i][j] = false;
        }
    }
    *minVertices = grafo.nVertices+1;
    Vertice maxGrado = grafo.maxGrado();
    cout << "Nodo raiz " << maxGrado.id <<" : ";
    recorridoAnchura(grafo, maxGrado.id, verticesCogidos, verticesRecorridos, vertices, arbol); 
    quitarHojas(grafo, maxGrado.id, vertices, arbol);
    for (int i = 0; i < grafo.nVertices; i++) verticesCogidos[i] = false;
    for (int i = 0; i < grafo.nVertices; i++) verticesRecorridos[i] = false;
    checkVertices(grafo, minVertices, verticesCogidos, vertices, verticesFinal);
    return *verticesFinal;
}

void Algoritmos::recorridoAnchura(Grafo &grafo, int origen, bool* verticesCogidos, bool* verticesRecorridos, vector<Vertice> *vertices, bool** arbol) {
    //cout << "Soy nodo " << origen << endl;
    
    bool* hijos=new bool[grafo.nVertices];
    verticesCogidos[origen] = true;
    verticesRecorridos[origen] = false;
    
    for (int i = 0; i < grafo.nVertices; i++) hijos[i] = false;

    for (int i = 0; i < grafo.nVertices; i++) {
        //cout << "Inspecciono " << origen <<" "<< i <<endl;
        if (grafo.matrix[origen][i] && !verticesRecorridos[i] && !verticesCogidos[i] && i != origen) {
            //cout << "Expando hijo " << i << endl;
            arbol[origen][i] = true;
            hijos[i] = true;
            verticesRecorridos[i] = true;
        }
        else arbol[origen][i] = false;   
    }
    for (int i = 0; i < grafo.nVertices; i++) { 
        for (int j = 0; j < grafo.nVertices; j++) {
            if (grafo.matrix[i][j] && verticesRecorridos[j] && !verticesCogidos[j] && i != j){
                //cout <<"Recorro nodo pendiente " << j << endl; 
                verticesCogidos[i] = true;
                recorridoAnchura(grafo, j, verticesCogidos, verticesRecorridos, vertices, arbol);
            } 
        }
    }
    for (int i = 0; i < grafo.nVertices; i++) {
        if (hijos[i]) {
            //cout << "Recorro hijo " << i << endl;
            recorridoAnchura(grafo, i, verticesCogidos, verticesRecorridos, vertices, arbol);
            break;
        }
    }
    delete hijos;
}

void Algoritmos::quitarHojas(Grafo &grafo,int origen,vector<Vertice> *vertices,bool** arbol){
    bool coger = true;
    bool* hojas = new bool[grafo.nVertices];
    for(int i = 0; i < grafo.nVertices; i++){
        hojas[i] = false;
    }
    for(int i = 0; i < grafo.nVertices; i++){
        for(int j = 0; j < grafo.nVertices; j++){
            
            if(arbol[i][j]){
                hojas[i] = true;
            }
        }
    }
    for(int i = 0; i < grafo.nVertices; i++){
        if(hojas[i]){
            vertices->push_back(i);
        }
    }
    delete hojas;
}

vector<Vertice> Algoritmos::greedyAlgorithm(Grafo grafo){
    vector<Vertice>* vertices = new vector<Vertice>();
    int v = 0;
    int total = 0;
    bool verticesCogidos[grafo.nVertices];
    for(int i = 0; i < grafo.nVertices; i++){
        verticesCogidos[i] = false;
    }

    while(total < grafo.nVertices){
        Vertice maxVertice = grafo.maxGrado();
        //cout << "Maximo grado " << maxVertice.grado <<" vertice " << maxVertice.id <<endl;
        for(int i = 0; i < grafo.nVertices;i++){
            //cout << grafo.matrix[maxVertice.id][i] << " " << grafo.matrix[i][maxVertice.id] << endl;
            if((grafo.matrix[maxVertice.id][i] || grafo.matrix[i][maxVertice.id]) && !verticesCogidos[i]){
                verticesCogidos[i] = true;
                total++;
                const int limit = grafo.nVertices ;
                progresscpp::ProgressBar progressBar(limit, 70);
                //cout << "Nuevo vertice: " <<i<< " total de vertices " << total<<endl;
            }
        }
        if(!verticesCogidos[maxVertice.id]){
            total++;
            verticesCogidos[maxVertice.id] = true;
        }
        vertices->push_back(maxVertice);
        grafo.deleteVertice(maxVertice);

    }
    return *vertices;

}