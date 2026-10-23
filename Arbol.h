#ifndef Arbol_H
#define Arbol_H

#include <iostream>
using namespace std;
#include <string>
#include "Especie.h"


class Arbol{
    private:
    string assetnum_;
    int num_parque_;
    int num_distrito_;
    int num_barrio_;
    double X_;
    double Y_;
    float perimetro_;
    float altura_;

    Especie* especieAsociada_;
    public:
    Arbol(string assetnum, int num_parque, int num_distrito, int num_barrio, double X, double Y, 
    float perimetro, float altura);
    Arbol();
    string get_assetnum() const;
    float get_altura() const;
    int get_num_parque() const;
        
        
    void setEspecie(Especie* e);
    string getCodEspecie() const;
    string getTipoEspecie() const;
    string getNbreComun() const;

    bool operator<(const Arbol& otro) const;
    bool operator==(const Arbol& otro) const;
};


#endif