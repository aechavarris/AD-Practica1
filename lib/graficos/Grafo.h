#pragma once


#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef _Grafo
#define _Grafo

class Grafo {
    private:
        vector<Arista> aristas;
    public:
        /*
         * Constructor de la clase Grafo
         */
        Grafo();
        Grafo (vector<Arista> aristas);

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        void addArista(Arista);

        int minGrado();

        int maxGrado();

        string toString();
};

#include  "Grafo.cpp"
#endif