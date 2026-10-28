#ifndef CONTROLPARQUES_H
#define CONTROLPARQUES_H

#include <iostream>
#include <string>
using namespace std;

#include "Especie.h"
#include "Parque.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Iterador.h"
#include "AVL.h"

class ControlParques {
private:
    VDinamico<Especie> varieties;
    ListaDEnlazada<Parque> parks;
    AVL<Arbol> trees;

public:
    ControlParques();
    ControlParques(const string& rutaEspecies, const string& rutaParques, const string& rutaArboles);

    int contarEspecieParque(string ncomun);
    VDinamico<Especie> listadoEspecieSubNbre(string cadena);
    Parque* buscarParque(const string& nbre_parque);

    Arbol* buscarArbol(string asNum);
    VDinamico<Arbol*> buscarArbolesRango(const string& asNumMin, const string& asNumMax);
    VDinamico<Arbol*> listaArbParque(string nbre_parque);
    Arbol* arbolMasAlto();
    int contarEspecies(string nbre_parque);
    int contarTipos();

    VDinamico<Especie>& get_varieties();
    const VDinamico<Especie>& get_varieties() const;
    ListaDEnlazada<Parque>& get_parks();
    const ListaDEnlazada<Parque>& get_parks() const;
    ListaDEnlazada<Parque>& get_nbre_parque();
    const ListaDEnlazada<Parque>& get_nbre_parque() const;
};

#endif