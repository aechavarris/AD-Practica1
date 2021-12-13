/*****************************************************************
 * File:    Grafo.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Grafo
 *****************************************************************/

#pragma once

#include <limits.h>
#include "Grafo.h"
#include "../vertice/Vertice.h"

Grafo::Grafo(const int n) {
    this->nVertices = n;
    int** m;
    m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
        for(int j = 0; j < n; j++){
            m[i][j] = 0;
        }
    }
    this->matrix = m;
};

void Grafo::addArista(Arista arista) {
    bool encontrado1 = false;
    bool encontrado2 = false;
    bool existente = false;

    for (int i = 0; i < this->aristas.size(); i++) {

        // Caso en el que la arista que se quiere añadir ya existe en el grafo
        if (this->aristas.at(i).v1.id == arista.v1.id && this->aristas.at(i).v2.id == arista.v2.id) existente = true;
        if (this->aristas.at(i).v2.id == arista.v1.id && this->aristas.at(i).v1.id == arista.v2.id) existente = true;
    }

    for (int i = 0; i < this->aristas.size(); i++) {  

        // Casos estandar
        if (arista.v1.id == this->aristas.at(i).v1.id && !existente) {
            this->aristas.at(i).v1.grado++;
            arista.v1.grado = this->aristas.at(i).v1.grado;
            encontrado1 = true;
        }
        else if (arista.v1.id == this->aristas.at(i).v2.id && !existente) { 
            this->aristas.at(i).v2.grado++;
            arista.v1.grado = this->aristas.at(i).v2.grado;
            encontrado1 = true;
        }
        else if (arista.v2.id == this->aristas.at(i).v1.id && !existente) {
            this->aristas.at(i).v1.grado++;
            arista.v2.grado = this->aristas.at(i).v1.grado;
            encontrado2 = true;
        }
        else if (arista.v2.id == this->aristas.at(i).v2.id && !existente) {
            this->aristas.at(i).v2.grado++;
            arista.v2.grado = this->aristas.at(i).v2.grado;
            encontrado2 = true;
        }
    }

    if (!encontrado1) arista.v1.grado = 1;
    if (!encontrado2) arista.v2.grado = 1;

    if (!existente) this->aristas.push_back(arista);

    this->matrix[arista.v1.id][arista.v2.id] = 1;
};

Vertice Grafo::minGrado() {
    int minGrado = INT_MAX, gradoV1 = 0, gradoV2 = 0;
    Vertice minimo;

    for (int i = 0; i < this->aristas.size(); i++) {
        gradoV1 = this->aristas.at(i).v1.grado;
        gradoV2 = this->aristas.at(i).v2.grado;

        if (gradoV1 < minGrado || gradoV2 < minGrado) minimo = gradoV1 <= gradoV2 ? this->aristas.at(i).v1 : this->aristas.at(i).v2;
        minGrado = minGrado > minimo.grado ? minimo.grado : minGrado;
    }  
    return minimo;
};

Vertice Grafo::maxGrado() {
    int maxGrado = 0, gradoV1 = 0, gradoV2 = 0;
    Vertice maximo;

    for (int i = 0; i < this->aristas.size(); i++) {
        gradoV1 = this->aristas.at(i).v1.grado;
        gradoV2 = this->aristas.at(i).v2.grado;

        if (gradoV1 > maxGrado || gradoV2 > maxGrado) maximo = gradoV1 >= gradoV2 ? this->aristas.at(i).v1 : this->aristas.at(i).v2;
        maxGrado = maxGrado < maximo.grado ? maximo.grado : maxGrado;
    }
    return maximo;
};

void Grafo::deleteVertice(Vertice v){
    //cout << "Borro vertice " << v.id<<endl;
    auto i = this->aristas.begin();
    int verticesContacto[this->nVertices];
    for(int i = 0; i < this->nVertices; i++){
        verticesContacto[i] = 0;
    }
    while(i < this->aristas.end()){
        //cout << "Miro arista " << i->toString()<<endl;
        if(i->v1.id == v.id ){
            verticesContacto[i->v2.id]++;
            //cout << "Erase" << endl;
            this->aristas.erase(i);
        }else if(i->v2.id == v.id){
            verticesContacto[i->v1.id]++;
            //cout << "Erase" << endl;
            this->aristas.erase(i);
        }else{
            i++;
        }
    }
    i = this->aristas.begin();
    while(i < this->aristas.end()){
        //cout << "Miro arista " << i->toString()<<endl;
        if(verticesContacto[i->v1.id]){
            //cout << "Disminuyo grado en " << verticesContacto[i->v1.id] << endl;
            i->v1.grado = i->v1.grado - verticesContacto[i->v1.id];
        }else if(verticesContacto[i->v2.id]){
            //cout << "Disminuyo grado en " << verticesContacto[i->v2.id] << endl;
            i->v2.grado = i->v2.grado - verticesContacto[i->v2.id];
        }
        i++;
    }
    for (int i = 0; i < this->nVertices; i++) {
        for(int j = 0; j < this->nVertices; j++){
            if(i == v.id || j == v.id){
                this->matrix[i][j] = 0;
            }
        }
    }
}

string Grafo::toString() {
    string ret = "[ ";

    for (int i = 0; i < this->aristas.size(); i++) {
        ret = ret + this->aristas.at(i).toString();
        if (i < this->aristas.size() - 1) ret = ret + ", ";
    }
    return ret + " ]";
};