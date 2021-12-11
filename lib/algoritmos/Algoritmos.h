/*****************************************************************
 * File:    Algoritmos.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Clase que contiene los diferentes algoritmos que se 
 *          van a utilizar para resolver el problema dado
 *****************************************************************/

#pragma once

#include "../../lib/grafos/grafo/Grafo.h"

using namespace std;

#ifndef _Algoritmos
#define _Algoritmos

class Algoritmos {
    public:
        
        /*
         * Constructor de la clase AlgoritmoTree
         */
        Algoritmos();


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        vector<Vertice> spanningTreeProfundidad(Grafo grafo);  

        /*
         * Pre:
         * Post:
         */
        bool recorridoProfundidad(Grafo &grafo, int origen, bool* verticesCogidos,vector<Vertice> *vertices);  

        /*
         * Pre:
         * Post:
         */
        void checkVertices(Grafo grafo,int* minVertices,bool* verticesCogidos,vector<Vertice> *vertices,vector<Vertice> *verticesFinal);

        /*
         * Pre:
         * Post:
         */
        vector<Vertice> spanningTreeAnchura(Grafo grafo);  

        /*
         * Pre:
         * Post:
         */
        void recorridoAnchura(Grafo &grafo, int origen, bool* verticesCogidos,bool* verticesRecorridos,vector<Vertice> *vertices, int** arbol);

        /*
         * Pre:
         * Post:
         */
        void quitarHojas(Grafo &grafo,int origen,vector<Vertice> *vertices, int** arbol);

        /*
         * Pre:
         * Post:
         */
        bool esHoja(Grafo grafo,int** arbol,int origen);
};

#include  "Algoritmos.cpp"
#endif