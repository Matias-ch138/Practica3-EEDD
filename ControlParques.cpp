#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "ControlParques.h"
#include "LectorCSV.h"
using namespace std;
static bool leerCampoCSV(const string& linea, size_t& posicion, string& campo, char separador = ',') {
    campo.clear();
    bool entreComillas = posicion < linea.size() && linea[posicion] == '"';
    if (entreComillas) {
        ++posicion;
    }

    while (posicion < linea.size()) {
        char caracter = linea[posicion];
        if (entreComillas && caracter == '"') {
            if (posicion + 1 < linea.size() && linea[posicion + 1] == '"') {
                campo += '"';
                posicion += 2;
            } else {
                entreComillas = false;
                ++posicion;
            }
        } else if (!entreComillas && caracter == separador) {
            ++posicion;
            return true;
        } else {
            campo += caracter;
            ++posicion;
        }
    }

    return !entreComillas;
}

static bool leerRegistroArbol(const string& linea, string campos[], size_t numeroCampos) {
    size_t posicion = 0;
    for (size_t i = 0; i < numeroCampos; ++i) {
        if (!leerCampoCSV(linea, posicion, campos[i], ';')) {
            return false;
        }
        if (i + 2 < numeroCampos && posicion == linea.size()) {
            return false;
        }
    }
    return posicion == linea.size();
}

static float leerMedidaCSV(const string& campo) {
    if (campo.empty()) {
        return 0.0f;
    }
    string normalizado = campo;
    replace(normalizado.begin(), normalizado.end(), ',', '.');
    return stof(normalizado);
}

static Especie* buscarEspecie(VDinamico<Especie>& especies, const string& codigo) {
    int inicio = 0;
    int fin = static_cast<int>(especies.gettLogico()) - 1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        const string& codigoMedio = especies[medio].get_codigo_especie();
        if (codigoMedio == codigo) {
            return &especies[medio];
        }
        if (codigoMedio < codigo) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return nullptr;
}

static Parque* buscarParquePorCodigo(ListaDEnlazada<Parque>& parques, int codigo) {
    Iterador<Parque> it = parques.iteradorInicio();
    while (!it.fin()) {
        if (it.getdato().get_cod_parque() == codigo) {
            return &it.getdato();
        }
        it.avanza();
    }
    return nullptr;
}
ControlParques::ControlParques(){
    
}
ControlParques::ControlParques(const string& rutaEspecies, const string& rutaParques, const string& rutaArboles){
    LectorCSV lector;
    lector.cargar(varieties, rutaEspecies);
    varieties.ordenar();

    ifstream fichero(rutaParques);
    if (fichero.is_open()) {
        string linea;
        while (getline(fichero, linea)) {
            if (linea.empty()) continue;
            
            string cod_str, nombre_parque;
            size_t posicion = 0;

            if (leerCampoCSV(linea, posicion, cod_str) &&
                leerCampoCSV(linea, posicion, nombre_parque)) {
                try {
                    int cod = stoi(cod_str);
                    Parque p(cod, nombre_parque);
                    parks.insertaFin(p);
                } catch (const invalid_argument& e) {
                    continue;
                }
            }
        }
        fichero.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo de parques: " << rutaParques << endl;
    }

    ifstream ficheroArboles(rutaArboles);
    if (!ficheroArboles.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de arboles: " << rutaArboles << endl;
        return;
    }

    string lineaArbol;
    getline(ficheroArboles, lineaArbol);
    while (getline(ficheroArboles, lineaArbol)) {
        if (!lineaArbol.empty() && lineaArbol.back() == '\r') {
            lineaArbol.pop_back();
        }
        if (lineaArbol.empty()) {
            continue;
        }

        string campos[12];
        if (!leerRegistroArbol(lineaArbol, campos, 12) || campos[0].empty()) {
            continue;
        }

        try {
            string x = campos[6];
            string y = campos[7];
            replace(x.begin(), x.end(), ',', '.');
            replace(y.begin(), y.end(), ',', '.');
            Arbol arbol(campos[0], stoi(campos[1]), stoi(campos[2]), campos[3],
                        stoi(campos[4]), campos[5], stod(x), stod(y),
                        leerMedidaCSV(campos[10]), leerMedidaCSV(campos[11]));
            arbol.setEspecie(buscarEspecie(varieties, campos[8]));

            if (!trees.inserta(arbol)) {
                continue;
            }

            Arbol* arbolAlmacenado = trees.buscaRec(arbol);
            Parque* parque = buscarParquePorCodigo(parks, arbol.get_num_parque());
            if (parque != nullptr) {
                parque->insertarArbol(arbolAlmacenado);
            }
        } catch (const exception&) {
            continue;
        }
    }
}


int ControlParques::contarEspecieParque(string ncomun){
    int contador = 0;
    Iterador<Parque> it = parks.iteradorInicio();
    while(!it.fin()){
        if(it.getdato().existeNbreCom(ncomun)){
            contador++;
        }
        it.avanza();
    }
    return contador;
}

VDinamico<Especie> ControlParques::listadoEspecieSubNbre(string cadena){
    VDinamico<Especie> resultados;
    for(int i=0; i<varieties.gettLogico(); i++){
        if(varieties[i].getnombre_cientifico().find(cadena) != string::npos){
            resultados.insertar(varieties[i]);
        }
    }
    return resultados;
}

Parque* ControlParques::buscarParque(const string& nbre_parque){
    Iterador<Parque> it = parks.iteradorInicio();
    while(!it.fin()){
        if(it.getdato().get_nbre_parque() == nbre_parque){
            return &it.getdato();
        }
      it.avanza();  
    }
    return nullptr;
}


VDinamico<Especie>& ControlParques::get_varieties(){
    return varieties;
}

const VDinamico<Especie>& ControlParques::get_varieties() const{
    return varieties;
}

ListaDEnlazada<Parque>& ControlParques::get_parks(){
    return parks;
}

const ListaDEnlazada<Parque>& ControlParques::get_parks() const{
    return parks;  
}

ListaDEnlazada<Parque>& ControlParques::get_nbre_parque(){
    return parks;
}

const ListaDEnlazada<Parque>& ControlParques::get_nbre_parque() const{
    return parks;
}

Arbol* ControlParques::buscarArbol(string asNum){
    Arbol aux;
    aux.set_assetnum(asNum);
    return trees.buscaRec(aux);
}
VDinamico<Arbol*> ControlParques::buscarArbolesRango(const string& asNumMin, const string& asNumMax){
    if (asNumMax < asNumMin) {
        throw invalid_argument("El limite inferior supera al limite superior");
    }
    Arbol minimo;
    Arbol maximo;
    minimo.set_assetnum(asNumMin);
    maximo.set_assetnum(asNumMax);
    return trees.recorreRango(minimo, maximo);
}
VDinamico<Arbol*> ControlParques::listaArbParque(string nbre_parque){
    Parque* parque = buscarParque(nbre_parque);
    if (parque != nullptr) {
        return parque->get_contains();
    }
    return VDinamico<Arbol*>();
}
Arbol* ControlParques::arbolMasAlto(){
    Arbol* arbolMasAlto=nullptr;
    Iterador<Parque> it = parks.iteradorInicio();
    while(!it.fin()){
        Arbol* mayorParque=it.getdato().arbolMasAlto();
        if(mayorParque != nullptr){
            if(arbolMasAlto==nullptr || mayorParque->get_altura()>arbolMasAlto->get_altura()){
                arbolMasAlto=mayorParque;
            }
        }
        it.avanza();
    }
    return arbolMasAlto;
}
int ControlParques::contarEspecies(string nbre_parque){
    Parque* parque =buscarParque(nbre_parque);
    if(parque!=nullptr){
        return parque->contarEspecies();
    }
    return 0;
}
int ControlParques::contarTipos(){
    Iterador<Parque> it = parks.iteradorInicio();
    VDinamico<string> tiposUnicos;
    while(!it.fin()){
        const VDinamico<Arbol*> &arboles= it.getdato().get_contains();
        for (int i = 0; i < arboles.gettLogico(); i++){
            string tipo = arboles[i]->getTipoEspecie();
            if (tipo.empty()) {
                continue;
            }
            bool existe = false;
            for (int j = 0; j < tiposUnicos.gettLogico(); j++){
                if(tiposUnicos[j]==tipo){
                    existe=true;
                    break;
                }
            }
            if(!existe){
                tiposUnicos.insertar(tipo);
            }
            
        }
        
        it.avanza();
    }
    return tiposUnicos.gettLogico();
}

unsigned int ControlParques::numArboles() const {
    return trees.numElementos();
}

unsigned int ControlParques::alturaArboles() const {
    return trees.altura();
}