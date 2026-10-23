#include "Arbol.h"
Arbol::Arbol(string assetnum, int num_parque, int num_distrito, int num_barrio, double X, double Y,
      float perimetro, float altura){
        assetnum_ = assetnum;
        num_parque_ = num_parque;
        num_distrito_ = num_distrito;
        num_barrio_ = num_barrio;
        X_ = X;
        Y_ = Y;
        perimetro_ = perimetro;
        altura_ = altura;
        especieAsociada_ = nullptr;
      }
Arbol::Arbol(){
    assetnum_ = "";
    num_parque_ = 0;
    num_distrito_ = 0;
    num_barrio_ = 0;
    X_ = 0;
    Y_ = 0;
    perimetro_ = 0;
    altura_ = 0;
    especieAsociada_ = nullptr;
}
string Arbol::get_assetnum() const{
    return assetnum_;
}
float Arbol::get_altura() const{
return altura_;
}
int Arbol::get_num_parque() const{
return num_parque_;
}

void Arbol::setEspecie(Especie *e){
    this->especieAsociada_=e;
}
string Arbol::getCodEspecie() const{
    return especieAsociada_->get_codigo_especie();
}
string Arbol::getTipoEspecie() const{
    return especieAsociada_->gettipo_planta();
}
string Arbol::getNbreComun() const{
    return especieAsociada_->getnombre_comun();
}

bool Arbol::operator<(const Arbol &otro) const{
    return assetnum_ < otro.assetnum_;
}
bool Arbol::operator==(const Arbol &otro) const{
    return assetnum_==otro.assetnum_;
}