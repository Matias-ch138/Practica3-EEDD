#include "Parque.h"
/**
 * @brief Constructor por defecto de un Parque
 * 
 */
Parque::Parque() : cod_parque(0), nbre_parque("") {}
/**
 * @brief Constructor parametrizado de un Parque
 * 
 * @param cod codigo del parque
 * @param nombre nombre del parque
 */
Parque::Parque(int cod, string nombre) : cod_parque(cod), nbre_parque(nombre) {}
/**
 * @brief Destructor de un Parque
 * 
 */
Parque::~Parque() = default;
/**
 * @brief obtener el codigo de un parque
 * 
 * @return int codigo obtenido del parque
 */
int Parque::get_cod_parque() const {
    return cod_parque;
}
/**
 * @brief establecer el codigo de un parque
 * 
 * @param cod codigo a establecer del parque
 */
void Parque::set_cod_parque(int cod) {
    cod_parque = cod;
}
/**
 * @brief obtener el nombre del parque
 * 
 * @return string nombre obtenido del parque
 */
string Parque::get_nbre_parque() const {
    return nbre_parque;
}   
/**
 * @brief establecer el nombre del parque
 * 
 * @param nombre nombre a establecer del parque
 */
void Parque::set_nbre_parque(string nombre) {
    nbre_parque = nombre;
}


/**
 * @brief arboles de un parque
 * 
 * @return VDinamico<Arbol*> arboles obtenidas de un parque
 */
const VDinamico<Arbol*>& Parque::get_contains()const{
    return contains_;
}

/**
 * @brief existe un nombre comun
 * 
 * @param ncomun el nombre comun
 * @return true si existe
 * @return false si no existe
 */
bool Parque::existeNbreCom(string ncomun) {
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i) {
        if (contains_[i]->getNbreComun() == ncomun) {
            return true;
        }
    }
    return false;
}
/**
 * @brief Inserta un arbol en un parque
 * 
 * @param arbol arbol que queremos insertar
 */
void Parque::insertarArbol(Arbol *arbol){
    contains_.insertar(arbol);
}
/**
 * @brief obtener el arbol mas alto del parque
 * 
 * @return Arbol* puntero al arbol mas alto del parque
 */
Arbol* Parque::arbolMasAlto(){
    if (contains_.gettLogico() == 0) {
        return nullptr;
    }
    Arbol *amayor= contains_[0];
    for(unsigned int i=0;i<contains_.gettLogico();i++){
        if(contains_[i]->get_altura()>amayor->get_altura()){
            amayor=contains_[i];
        }
    }
    return amayor;
}
/**
 * @brief Cuenta las especies únicas de un parque
 * 
 * @return int número de especies únicas del parque
 */
int Parque::contarEspecies(){
    VDinamico<string> especiesUnicas;
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i){
        string cod = contains_[i]->getCodEspecie();
        bool existe = false;
        for (unsigned int j = 0; j < especiesUnicas.gettLogico(); ++j){
            if (especiesUnicas[j] == cod){
                existe = true;
                break;
            }
        }
        if (!existe&&!cod.empty()){
            especiesUnicas.insertar(cod);

        }
    }
    return especiesUnicas.gettLogico();
}
/**
 * @brief cuenta los tipos únicos de un parque
 * 
 * @return int número de tipo únicos de un parque
 */
int Parque::contarTipos(){
    VDinamico<string> tiposUnicos;
    for(unsigned int i=0;i<contains_.gettLogico();i++){
        string tiposunicos= contains_[i]->getTipoEspecie();
        bool existe=false;
        for(unsigned int j=0;j<tiposUnicos.gettLogico();j++){
            if(tiposUnicos[j]==tiposunicos){
                existe=true;
                break;
            }
        }
        if(!existe&&!tiposunicos.empty()){
            tiposUnicos.insertar(tiposunicos);
        }
    }
    return tiposUnicos.gettLogico();
}