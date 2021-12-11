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
    for(int i = 0; i < grafo.nVertices; i++){
        if(!verticesCogidos){
            check = false;
        }
    }
    cout <<"Vertices ";
    for(auto i : *vertices){
        cout<< i.id << " ";
    }
    cout << endl;
    if(vertices->size()<= *minVertices && check){
        *minVertices = vertices->size();
        verticesFinal->clear();
        for(auto i : *vertices){
            verticesFinal->push_back(i);
        }
    }
    vertices->clear();
}

vector<Vertice> Algoritmos::spanningTreeProfundidad(Grafo grafo){
    vector<Vertice>* vertices = new vector<Vertice>();
    vector<Vertice>* verticesFinal = new vector<Vertice>();
    bool* verticesCogidos = new bool[grafo.nVertices];
    bool end = false;
    for(int i = 0; i < grafo.nVertices; i++){
        verticesCogidos[i] = false;
    }
    int* minVertices = new int;
    *minVertices = grafo.nVertices+1;
    for(int n = 0; n < grafo.nVertices; n++){
        cout << "Nodo raiz: " << n << endl;
        recorridoProfundidad(grafo,n,verticesCogidos,vertices);   
        for(int i = 0; i < grafo.nVertices; i++){
            verticesCogidos[i] = false;
        }
        checkVertices(grafo,minVertices,verticesCogidos,vertices,verticesFinal);
    }
    return *verticesFinal;

}

bool Algoritmos::recorridoProfundidad(Grafo &grafo, int origen, bool* verticesCogidos,vector<Vertice> *vertices){
    bool hoja = true;
    for(int i = 0; i < grafo.nVertices; i++){
        if(grafo.matrix[origen][i]==1 && !verticesCogidos[i]){
            hoja = false;
        }
    }

    if(hoja) return true;

    for(int i = 0; i < grafo.nVertices; i++){
        //cout << "Inspecciono " << origen <<" "<< i <<endl;
        if(grafo.matrix[origen][i]==1 && !verticesCogidos[i] && i != origen){
            verticesCogidos[origen]=true;
            if(!recorridoProfundidad(grafo, i, verticesCogidos, vertices)){
               verticesCogidos[origen]=false;
                cout << "Selecciono arista (" << origen << "," << i << ")" << endl; 
                vertices->push_back(Vertice(origen));
                verticesCogidos[i]=true;
            }
        }
    }
    return false;
}

bool Algoritmos::esHoja(Grafo grafo,int origen, bool* verticesCogidos){
    bool hoja = true;
    for(int i = 0; i < grafo.nVertices; i++){
        if(grafo.matrix[origen][i]==1 && !verticesCogidos[i]){
            hoja = false;
        }
    }

    if(hoja) return true;
    return false;
}

vector<Vertice> Algoritmos::spanningTreeAnchura(Grafo grafo){
    vector<Vertice>* vertices = new vector<Vertice>();
    vector<Vertice>* verticesFinal = new vector<Vertice>();
    bool* verticesCogidos = new bool[grafo.nVertices];
    bool end = false;
    for(int i = 0; i < grafo.nVertices; i++){
        verticesCogidos[i] = false;
    }
    int* minVertices = new int;
    *minVertices = grafo.nVertices+1;
    for(int n = 0; n < grafo.nVertices; n++){
        cout << "Nodo raiz: " << n << endl;
        recorridoAnchura(grafo,n,verticesCogidos,vertices);   
        for(int i = 0; i < grafo.nVertices; i++){
            verticesCogidos[i] = false;
        }
        checkVertices(grafo,minVertices,verticesCogidos,vertices,verticesFinal);
    }
    return *verticesFinal;

}

void Algoritmos::recorridoAnchura(Grafo &grafo, int origen, bool* verticesCogidos,vector<Vertice> *vertices){
    bool hijos[grafo.nVertices];
    for(int i = 0; i < grafo.nVertices; i++){
        hijos[i] = false;
    }
    int** m;
    m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
    }
    for(int i = 0; i < grafo.nVertices; i++){
        //cout << "Inspecciono " << origen <<" "<< i <<endl;
        if(grafo.matrix[origen][i]==1 && !verticesCogidos[i] && i != origen){
            verticesCogidos[origen]=true;
            if(!esHoja(grafo,i,verticesCogidos)){
                cout << "Selecciono arista (" << origen << "," << i << ")" << endl; 
                vertices->push_back(Vertice(i));
                hijos[i] = true;
            }
            verticesCogidos[i]=true;
        }
    }
    for(int i = 0; i < grafo.nVertices; i++){
        if(hijos[i]){
            verticesCogidos[i]=true;
            recorridoAnchura(grafo,i,verticesCogidos,vertices);
        }
    }
}