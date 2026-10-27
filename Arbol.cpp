#include "Arbol.h"

// --- CONSTRUCTORES ---
Arbol::Arbol(string assetnum, int num_parque, int num_distrito, string nbre_distrito, 
             int num_barrio, string nbre_barrio, double X, double Y, 
             float perimetro, float altura) {
    assetnum_ = assetnum;
    num_parque_ = num_parque;
    num_distrito_ = num_distrito;
    nbre_distrito_ = nbre_distrito;
    num_barrio_ = num_barrio;
    nbre_barrio_ = nbre_barrio;
    X_ = X;
    Y_ = Y;
    perimetro_ = perimetro;
    altura_ = altura;
    especieAsociada_ = nullptr;
}

Arbol::Arbol() {
    assetnum_ = "";
    num_parque_ = 0;
    num_distrito_ = 0;
    nbre_distrito_ = "";
    num_barrio_ = 0;
    nbre_barrio_ = "";
    X_ = 0;
    Y_ = 0;
    perimetro_ = 0;
    altura_ = 0;
    especieAsociada_ = nullptr;
}

// --- GETTERS ---
string Arbol::get_assetnum() const { return assetnum_; }
int Arbol::get_num_parque() const { return num_parque_; }
int Arbol::get_num_distrito() const { return num_distrito_; }
string Arbol::get_nbre_distrito() const { return nbre_distrito_; }
int Arbol::get_num_barrio() const { return num_barrio_; }
string Arbol::get_nbre_barrio() const { return nbre_barrio_; }
double Arbol::get_X() const { return X_; }
double Arbol::get_Y() const { return Y_; }
float Arbol::get_perimetro() const { return perimetro_; }
float Arbol::get_altura() const { return altura_; }

// --- SETTERS ---
void Arbol::set_assetnum(const string& assetnum) { assetnum_ = assetnum; }
void Arbol::set_num_parque(int num_parque) { num_parque_ = num_parque; }
void Arbol::set_num_distrito(int num_distrito) { num_distrito_ = num_distrito; }
void Arbol::set_nbre_distrito(const string& nbre_distrito) { nbre_distrito_ = nbre_distrito; }
void Arbol::set_num_barrio(int num_barrio) { num_barrio_ = num_barrio; }
void Arbol::set_nbre_barrio(const string& nbre_barrio) { nbre_barrio_ = nbre_barrio; }
void Arbol::set_X(double X) { X_ = X; }
void Arbol::set_Y(double Y) { Y_ = Y; }
void Arbol::set_perimetro(float perimetro) { perimetro_ = perimetro; }
void Arbol::set_altura(float altura) { altura_ = altura; }

// --- MÉTODOS DE ESPECIE ---
void Arbol::setEspecie(Especie *e) { 
    especieAsociada_ = e; 
}

string Arbol::getCodEspecie() const {
    if (especieAsociada_ == nullptr) return "";
    return especieAsociada_->get_codigo_especie();
}

string Arbol::getTipoEspecie() const {
    if (especieAsociada_ == nullptr) return "";
    return especieAsociada_->gettipo_planta();
}

string Arbol::getNbreComun() const {
    if (especieAsociada_ == nullptr) return "";
    return especieAsociada_->getnombre_comun();
}
string Arbol::getNbreCientifico() const {
    if (especieAsociada_ == nullptr) return "";
    return especieAsociada_->getnombre_cientifico();
}
// --- OPERADORES ---
bool Arbol::operator<(const Arbol &otro) const {
    return assetnum_ < otro.assetnum_;
}

bool Arbol::operator==(const Arbol &otro) const {
    return assetnum_ == otro.assetnum_;
}