#pragma once

#include "Arista.h"

Arista::Arista() {
};
Arista::Arista (Vertice v1, Vertice v2){
    this->v1 = v1;
    this->v2 = v2;
};

string Arista::toString (){
    return "("+ to_string(this->v1.id)  + ","+ to_string(this->v2.id)+")";
};