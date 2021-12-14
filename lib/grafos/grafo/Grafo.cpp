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
    bool** m;
    m = new bool*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new bool[n];
        for(int j = 0; j < n; j++){
            m[i][j] = false;
        }
    }
    this->matrix = m;
};
//DEPRECATED
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

    this->matrix[arista.v1.id][arista.v2.id] = true;
};

Vertice Grafo::minGrado() { 
    return this->grados.end()->id;
};

Vertice Grafo::maxGrado() {
    return this->grados.begin()->id;
};

void Grafo::deleteVertice(Vertice v){
    //cout << "Borro vertice " << v.id<<endl;
    this->grados.erase(grados.begin());
}

string Grafo::toString() {
    string ret = "[ ";

    for (int i = 0; i < this->aristas.size(); i++) {
        ret = ret + this->aristas.at(i).toString();
        if (i < this->aristas.size() - 1) ret = ret + ", ";
    }
    return ret + " ]";
};