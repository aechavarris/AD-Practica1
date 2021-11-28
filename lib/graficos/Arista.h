#pragma once

#include <iostream>
#include <vector>
using namespace std;

#ifndef _Arista
#define _Arista

class Arista {
    public:
        Vertice v1; //(v1,v2)
        Vertice v2;

        /*
         * Constructor de la clase Arista
         */
        Arista();
        Arista (Vertice v1, Vertice v2);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        string toString();
};

#include  "Arista.cpp"
#endif