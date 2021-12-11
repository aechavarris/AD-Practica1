/*****************************************************************
 * File:    Arista.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Clase utilizada para representar una arista
 *****************************************************************/

#pragma once

#include <iostream>
#include <vector>
#include "../vertice/Vertice.h"

using namespace std;

#ifndef _Arista
#define _Arista

class Arista {
    public:
        Vertice v1;
        Vertice v2;

        /*
         * Constructor de la clase Arista
         */
        Arista();
        Arista(Vertice v1, Vertice v2);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre: ---
         * Post: Devuelve, en formato string, los vértices
         *       que conforman la arista
         */
        string toString();
};

#include  "Arista.cpp"
#endif