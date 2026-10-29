#ifndef AVL_H
#define AVL_H
#include "VDinamico.h"
template <typename U> class NodoAVL {
public:
  NodoAVL<U> *izq, *der;
  U dato;
  char bal;
  /**
   * @brief Constructor de un NodoALV
   * 
   * @param ele es el elemento que hay dentro del nodo
   */
  NodoAVL(const U &ele) : izq(nullptr), der(nullptr), bal(0), dato(ele) {}
};
template <typename T> 
class AVL {
private:
  NodoAVL<T> *raiz;
  unsigned int num_elementos;
  /**
   * @brief método auxiliar para la copia de un arbol en preorden con métodos recursivos
   * 
   * @param p puntero a la raiz del arbol
   * @return NodoAVL<T>* puntero al nodo que va a ser copiado
   */
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
  /**
   * @brief método auxiliar para la destrucción de un arbol en postorden con métodos recursivos
   * 
   * @param p puntero a la raiz de un arbol
   */
  void destruyeArbol(NodoAVL<T> *p) {
    if (p != nullptr) {
      destruyeArbol(p->izq);
      destruyeArbol(p->der);
      delete p;
    }
  }
  /**
   * @brief método auxiliar para el calculo de la altura del arbol por recursividad
   * 
   * @param p puntero a la raiz del arbol
   * @return unsigned int altura del arbol
   */
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
  /**
   * @brief método auxiliar recursivo para guardar los elementos de un arbol en inorden en un VDinamico
   * 
   * @param p puntero a la raiz del arbol
   * @param v vector dinamico en el que se van a guardar los elementos del arbol
   */
  void inorden(NodoAVL<T> *p, VDinamico<T*> &v) const {
    if (p != nullptr) {
      inorden(p->izq, v);
      v.insertar(&(p->dato));
      inorden(p->der, v);
    }
  }
  /**
   * @brief método auxiliar recursivo para recorrer un rango en el arbol guardando ese rango en un VDinamico
   * 
   * @param p puntero a la raiz del arbol 
   * @param minimo el minimo del rango
   * @param maximo el máximo del rango
   * @param resultado el VDinamico con los datos guardados entre el @param minimo y @param maximo del arbol
   */
  void recorreRango(NodoAVL<T> *p, const T &minimo, const T &maximo,
                    VDinamico<T *> &resultado) const {
    if (p == nullptr) {
      return;
    }
    if (minimo < p->dato) {
      recorreRango(p->izq, minimo, maximo, resultado);
    }
    if (!(p->dato < minimo) && !(maximo < p->dato)) {
      resultado.insertar(&(p->dato));
    }
    if (p->dato < maximo) {
      recorreRango(p->der, minimo, maximo, resultado);
    }
  }
  /**
   * @brief Rotación hacia la derecha de un nodo para equilibrar el arbol
   * 
   * @param nodo nodo que queremos que se rote
   */
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
  /**
   * @brief Rotación hacia la izquierda de un nodo para equilibrar el arbol
   * 
   * @param nodo nodo que queremos que se rote
   */
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
  /**
   * @brief método auxiliar para la busqueda recursiva en el arbol
   * 
   * @param p la raiz del arbol
   * @param dato el dato a buscar en el arbol
   * @return NodoAVL<T>* el puntero al nodo que contiene ese dato
   */
  NodoAVL<T> *buscaRec(NodoAVL<T> *p, T &dato) const {
    if (p == nullptr)
      return nullptr;
    if (dato < p->dato)
      return buscaRec(p->izq, dato);
    if (p->dato < dato)
      return buscaRec(p->der, dato);
    return p; // Encontrado
  }
  /**
   * @brief método auxiliar recursivo para insertar un dato en el arbol
   * 
   * @param c puntero a la referencia de la raiz del arbol
   * @param dato el dato que queremos insertar en el arbol
   * @return 1 si se ha insertado 0 si ya estaba insertado de antes
   */
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
        c->bal += deltaH;
        if (c->bal == 2) {
          if (c->izq->bal == -1){
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
        c->bal -= deltaH;
        if (c->bal == -2) {
          if (c->der->bal == 1){
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
  /**
   * @brief Constructor por defecto de un arbolAVL
   * 
   */
  AVL() : raiz(nullptr), num_elementos(0) {
  }
  /**
   * @brief Constructor por copia de un arbolAVL
   * 
   * @param orig el arbol cuyos datos queremos inicializar en un nuevo arbol
   */
  AVL(const AVL<T> &orig) : raiz(nullptr), num_elementos(orig.num_elementos) {
    raiz = CopiaPreorden(orig.raiz);
  }
  /**
   * @brief Destructor del arbolAVL
   * 
   */
  ~AVL() {
    destruyeArbol(raiz);
    raiz = nullptr;
    num_elementos = 0;
  }
  /**
   * @brief Operador de asignación del arbolAVL
   * 
   * @param origen el arbol cuyos datos queremos asignar a otro arbol
   * @return AVL<T>& el arbol al que le hemos asignado los datos de @param origen
   */
  AVL<T>& operator=(const AVL<T> &origen) {
    if (this != &origen) {
      destruyeArbol(raiz);
      num_elementos = origen.num_elementos;
      raiz = CopiaPreorden(origen.raiz);
    }
    return *this;
  }
  /**
   * @brief método recursivo para insertar un nuevo elemento en el arbolAVL
   * 
   * @param dato dato que vamos a insertar
   * @return true si se ha insertado correctamente
   * @return false si ese dato ya estaba insertado antes
   */
  bool inserta(T &dato) {
    unsigned int tamAntes = num_elementos;
        inserta(raiz, dato);
        return num_elementos > tamAntes;
    return inserta(raiz, dato);
  }
  /**
   * @brief Método de busqueda recursiva
   * 
   * @param dato dato que queremos buscar
   * @return T* el puntero al dato encontrado
   */
  T *buscaRec(T &dato) {
    NodoAVL<T> *n = buscaRec(raiz, dato);
    if (n != nullptr) {
      return &(n->dato);
    } else {
      return nullptr;
    }
  }
  /**
   * @brief Método de busqueda iterativa
   * 
   * @param dato dato que queremos buscar
   * @return T* el puntero al dato encontrado
   */
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
  /**
   * @brief Guadado de todos los elementos del arbolAVL en inorden en un VDinamico 
   * 
   * @return VDinamico<T*> el vector dinamico con los elementos del arbolAVL en inorden
   */
  VDinamico<T*> recorreInorden() const {
    VDinamico<T *> v;
    inorden(raiz, v);
    return v;
  }
  /**
   * @brief Guardado de todos los elementos en cierto rango de un arbolAVL en un VDinamico
   * 
   * @param minimo el minimo del rango
   * @param maximo el maximo del rango
   * @return VDinamico<T *> el vector dinamico con los elementos del arbolAVl entre @param minimo y @param maximo
   */
  VDinamico<T*> recorreRango(const T &minimo, const T &maximo) const {
    VDinamico<T*> resultado;
    recorreRango(raiz, minimo, maximo, resultado);
    return resultado;
  }
  /**
   * @brief Devuelve el numero de elementos que hay en el arbolAVL
   * 
   * @return unsigned int el numero de elementos
   */
  unsigned int numElementos() const{
    return num_elementos;
  }
  /**
   * @brief Calculo de la altura del arbol
   * 
   * @return unsigned int altura del arbol
   */
  unsigned int altura() const{
    return calcularAltura(raiz);
  }
};

#endif