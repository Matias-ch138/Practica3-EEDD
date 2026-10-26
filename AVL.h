#ifndef AVL_H
#define AVL_H
#include "VDinamico.h"
template <typename U>
class NodoAVL{
    public:
    NodoAVL<U> *izq, *der;
    U dato;
    char bal;

    NodoAVL(U &ele): izq(0), der(0), bal(0), dato(ele){}
};
template <typename T>
class AVL{
private:
    NodoAVL<T> *raiz;
    int num_elementos; //Me cago en dios y los AVL que vuelvan los tiempos en los que los negros se podian comprar por un euro
    NodoAVL<T>* AVL<T>::CopiaPreorden(NodoAVL<T>* p) {
        if (p == nullptr){
            return nullptr;
        } 

        NodoAVL<T>* nuevo = new NodoAVL<T>(p->dato);
        nuevo->bal = p->bal;
        nuevo->izq = CopiaPreorden(p->izq);
        nuevo->der = CopiaPreorden(p->der);
    
        return nuevo;
    }
    void destruyeArbol(NodoAVL<T>* p){
        if(p != nullptr){
            destruyeArbol(p->izq);
            destruyeArbol(p->der);
            delete p;
        }
    }
    unsigned int calcularAltura(NodoAVL<T>* p){
        
        if(p!=nullptr){
            unsigned int altIzq = calcularAltura(p->izq);
            unsigned int altDer = calcularAltura(p->der);
            return 1 + (altIzq > altDer ? altIzq : altDer);
        }
    }
    void inorden(NodoAVL<T>* p, VDinamico<T*>& v) const {
        if (p != nullptr) {
            inorden(p->izq, v);         
            v.insertar(&(p->dato));     
            inorden(p->der, v);         
        }
    }
    public:
    AVL<T>();

    AVL(const AVL<T>& orig) : raiz(nullptr), num_elementos(orig.num_elementos) {
        raiz = CopiaPreorden(orig.raiz);
    }
    ~AVL<T>(){
        destruyeArbol(raiz);
        raiz = nullptr;
        num_elementos = 0;
    }

    AVL<T> operator =(const AVL<T> &origen){
        if(this != &origen){
        num_elementos=origen.num_elementos;
        raiz=CopiaPreorden(origen.raiz);
        
        }
        return *this;
    }
    void rotDer(Nodo<T>* &nodo){

    }
    rotIzq(Nodo<T>* &nodo){
        
    }
    bool inserta(T& dato){
        if(raiz.dato<dato){
            raiz->izq->dato=dato;
        }else{
            raiz->der->dato=dato;
        }
    }
    T* buscaRec(T &dato){

    }
    T* buscaIt(T &dato){

    }
    VDinamico<T*> recorreInorden(){
        VDinamico<T*> v;
        inorden(raiz, v);
        return v;
    }
    unsigned int numElementos(){
        return numElementos;
    }
    unsigned int altura(){
        

    }

};


#endif