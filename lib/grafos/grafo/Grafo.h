/*****************************************************************
 * File:    Grafo.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Clase utilizada para representar un grafo
 *****************************************************************/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../arista/Arista.h"

using namespace std;

#ifndef _Grafo
#define _Grafo

class Grafo {

    public:
        vector<Arista> aristas;
        int nVertices;
        bool** matrix;

        struct OrderNodo
        {
            bool operator()(Vertice v1,Vertice v2) const {
                    if (v1.grado == v2.grado ) {
                        return v1.id <= v2.id; 
                    } else {
                        return v1.grado > v2.grado;
                    }
                }
        };
        set<Vertice, OrderNodo> grados;

        /*
         * Constructor de la clase Grafo
         */
        Grafo(const int n);


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        void addArista(Arista arista);

        /*
         * Pre: ---
         * Post: Devuelve el vértice de menor grado del
         *       grafo
         */
        Vertice minGrado();

        /*
         * Pre: ---
         * Post: Devuelve el vértice de mayor grado del
         *       grafo
         */
        Vertice maxGrado();

        /*
         * Pre: 
         * Post: 
         */
        void deleteVertice(Vertice v);

        /*
         * Pre: --- 
         * Post: Devuelve, en formato string, las aristas
         *       que conforman el grafo
         */
        string toString();     
};

#include  "Grafo.cpp"
#endif