#ifndef AVL_H
#define AVL_H
#include "VDinamico.h"
template <typename U> class NodoAVL {
public:
  NodoAVL<U> *izq, *der;
  U dato;
  char bal;

  NodoAVL(const U &ele) : izq(nullptr), der(nullptr), bal(0), dato(ele) {}
};
template <typename T> 
class AVL {
private:
  NodoAVL<T> *raiz;
  unsigned int num_elementos;
  NodoAVL<T> *CopiaPreorden(NodoAVL<T> *p) {
    if (p == nullptr) {
      return nullptr;
    }

    NodoAVL<T> *nuevo = new NodoAVL<T>(p->dato);
    nuevo->bal = p->bal;
    nuevo->izq = CopiaPreorden(p->izq);
    nuevo->der = CopiaPreorden(p->der);

    return nuevo;
  }
  void destruyeArbol(NodoAVL<T> *p) {
    if (p != nullptr) {
      destruyeArbol(p->izq);
      destruyeArbol(p->der);
      delete p;
    }
  }
  unsigned int calcularAltura(NodoAVL<T> *p) const {

    if (p == nullptr)
      return 0;

    unsigned int altIzq = calcularAltura(p->izq);
    unsigned int altDer = calcularAltura(p->der);
    unsigned int alturaMayor;

    if (altIzq > altDer) {
      alturaMayor = altIzq;
    } else {
      alturaMayor = altDer;
    }
    return 1 + alturaMayor;
  }
  void inorden(NodoAVL<T> *p, VDinamico<T *> &v) const {
    if (p != nullptr) {
      inorden(p->izq, v);
      v.insertar(&(p->dato));
      inorden(p->der, v);
    }
  }
  void rotDer(NodoAVL<T> *&nodo) {
    NodoAVL<T> *q = nodo, *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) {
      q->bal -= l->bal;
    }
    l->bal--;
    if (q->bal < 0) {
      l->bal -= -q->bal;
    }
  }
  void rotIzq(NodoAVL<T> *&nodo) {
    NodoAVL<T> *q = nodo, *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) {
      q->bal += -r->bal;
    }
    r->bal++;
    if (q->bal > 0) {
      r->bal += q->bal;
    }
  }

  NodoAVL<T> *buscaRec(NodoAVL<T> *p, T &dato) const {
    if (p == nullptr)
      return nullptr;
    if (dato < p->dato)
      return buscaRec(p->izq, dato);
    if (p->dato < dato)
      return buscaRec(p->der, dato);
    return p; // Encontrado
  }
  int inserta(NodoAVL<T> *&c, T &dato) {
    int deltaH = 0;
    if (c == nullptr) {
      c = new NodoAVL<T>(dato);
      num_elementos++;
      return 1;
    }

    if (dato < c->dato) {
      deltaH = inserta(c->izq, dato);
      if (deltaH != 0) {
        c->bal -= deltaH;
        if (c->bal == -2) {
          if (c->izq->bal == 1){
            rotIzq(c->izq);
          }
          rotDer(c);
          return 0;
        }
        if(c->bal!=0){
          return 1;
        }else{
          return 0;
        }
      }
    } else if (c->dato < dato) {
      deltaH = inserta(c->der, dato);
      if (deltaH != 0) {
        c->bal += deltaH;
        if (c->bal == 2) {
          if (c->der->bal == -1){
            rotDer(c->der);
          }
          rotIzq(c);
          return 0;
        }
        if(c->bal!=0){
          return 1;
        }else{
          return 0;
        }
      }
    }
    return 0; 
  }

public:
  AVL() : raiz(nullptr), num_elementos(0) {
  }

  AVL(const AVL<T> &orig) : raiz(nullptr), num_elementos(orig.num_elementos) {
    raiz = CopiaPreorden(orig.raiz);
  }
  ~AVL() {
    destruyeArbol(raiz);
    raiz = nullptr;
    num_elementos = 0;
  }

  AVL<T>& operator=(const AVL<T> &origen) {
    if (this != &origen) {
      destruyeArbol(raiz);
      num_elementos = origen.num_elementos;
      raiz = CopiaPreorden(origen.raiz);
    }
    return *this;
  }

  bool inserta(T &dato) {
    unsigned int tamAntes = num_elementos;
        inserta(raiz, dato);
        return num_elementos > tamAntes;
    return inserta(raiz, dato);
  }
  T *buscaRec(T &dato) {
    NodoAVL<T> *n = buscaRec(raiz, dato);
    if (n != nullptr) {
      return &(n->dato);
    } else {
      return nullptr;
    }
  }
  T *buscaIt(T &dato) {
    NodoAVL<T> *n = raiz;
    while (n != nullptr) {
      if (dato == n->dato) {
        return &(n->dato);
      } else if (dato < n->dato) {
        n = n->izq;
      } else {
        n = n->der;
      }
    }
    return nullptr;
  }
  VDinamico<T *> recorreInorden() const {
    VDinamico<T *> v;
    inorden(raiz, v);
    return v;
  }
  unsigned int numElementos() const{
    return num_elementos;
  }
  unsigned int altura() const{
    return calcularAltura(raiz);
  }
};

#endif