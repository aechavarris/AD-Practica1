#pragma once
#include <limits.h>
#include "Grafo.h"

Grafo::Grafo() {
};

void Grafo::addArista(Arista arista){
    bool encontrado1 = false;
    bool encontrado2 = false;
    for (int i = 0; i < this->aristas.size();i++){
        if(this->aristas.at(i).v1.id == arista.v1.id && this->aristas.at(i).v2.id == arista.v2.id){
            cout<<"Esta arista ya existe: "<<arista.toString()<<endl;
            exit(1);
        }
        if(this->aristas.at(i).v2.id == arista.v1.id && this->aristas.at(i).v1.id == arista.v2.id){
            cout<<"Esta arista ya existe: "<<arista.toString()<<endl;
            exit(1);
        }
        if(arista.v1.id == this->aristas.at(i).v1.id ){
            this->aristas.at(i).v1.grado++;
            arista.v1.grado = this->aristas.at(i).v1.grado;
            encontrado1 = true;
        }else if (arista.v1.id == this->aristas.at(i).v2.id ){
            this->aristas.at(i).v2.grado++;
            arista.v1.grado = this->aristas.at(i).v2.grado;
            encontrado1 = true;
        }else if(arista.v2.id == this->aristas.at(i).v1.id ){
            this->aristas.at(i).v1.grado++;
            arista.v2.grado = this->aristas.at(i).v1.grado;
            encontrado2 = true;
        }else if (arista.v2.id == this->aristas.at(i).v2.id ){
            this->aristas.at(i).v2.grado++;
            arista.v2.grado = this->aristas.at(i).v2.grado;
            encontrado2 = true;
        }
    }
    if(!encontrado1){
        arista.v1.grado = 1;
    }
    if(!encontrado2){
        arista.v2.grado = 1;
    }
    this->aristas.push_back(arista);
    
};
int Grafo::minGrado(){
    int minGrado = INT_MAX;
    for (int i = 0; i < this->aristas.size();i++){
        if(this->aristas.at(i).v1.grado <minGrado){
            minGrado = this->aristas.at(i).v1.grado;
        }
        if(this->aristas.at(i).v2.grado <minGrado){
            minGrado = this->aristas.at(i).v2.grado;
        }
    }
    return minGrado;
}
int Grafo::maxGrado(){
    int maxGrado = 0;
    for (int i = 0; i < this->aristas.size();i++){
        if(this->aristas.at(i).v1.grado > maxGrado){
            maxGrado = this->aristas.at(i).v1.grado;
        }
        if(this->aristas.at(i).v2.grado > maxGrado){
            maxGrado = this->aristas.at(i).v2.grado;
        }
    }
    return maxGrado;
}
string Grafo::toString(){
    string ret = "[";

    for (int i = 0; i < this->aristas.size();i++){
        ret = ret + this->aristas.at(i).toString();
        if(i<this->aristas.size()-1){
            ret = ret + ",";
        }
    }
    
    return ret +"]";
}