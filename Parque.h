#ifndef PARQUE_H
#define PARQUE_H

#include <iostream>
#include <string>
#include "Especie.h"
#include "VDinamico.h"
#include "Arbol.h"
using namespace std;


class Parque {
private:
    int cod_parque;
    string nbre_parque;
    VDinamico<Arbol*> contains_;
public:
    Parque();
    Parque(int cod, string nombre);
    ~Parque();

    int get_cod_parque() const;
    void set_cod_parque(int cod);

    string get_nbre_parque() const;
    void set_nbre_parque(string nombre);
    VDinamico<Arbol> get_arboles() const;
    const VDinamico<Arbol*>& get_contains() const;

    void insertarArboles(Arbol &Arbol);
    bool existeNbreCom(string ncomun);
    bool existeNbreCie(string ncient);

    void insertarArbol(Arbol* arbol);   
    Arbol arbolMasAlto();
    int contarEspecies();
    int contarTipos();
};

#endif