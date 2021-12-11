/*****************************************************************
 * File:    Vertice.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Clase utilizada para representar un vértice
 *****************************************************************/

#pragma once

#include <iostream>
#include <vector>

using namespace std;

#ifndef _Vertice
#define _Vertice

class Vertice {
    public:
        int grado;
        int id;

        /*
         * Constructor de la clase Vertice
         */
        Vertice();
        Vertice(int id);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------
};

#include  "Vertice.cpp"
#endif