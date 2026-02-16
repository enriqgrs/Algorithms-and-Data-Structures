//*****************************************************************
// File:    coleccionesInterdependientes.hpp
// Authors: Anastasia Shlyk (NIP: 931807)
//          Enrique José Guaras Lacasta (NIP: 870709)
// Date:    Noviembre 2025
// Coms:    Practica 3 (EDA)
//*****************************************************************

#include "pila_dinamica.hpp"
#include <iostream>
#ifndef _COLECCIONES_INTERDEPENDIENTES_HPP
#define _COLECCIONES_INTERDEPENDIENTES_HPP
using namespace std;

/* INICIO DE LA PARTE PÚBLICA o INTERFAZ  */

/*Los valores del TAD genérico colecInterdep representan colecciones de
  elementos interdependientes. Donde cada uno de sus elementos se forman
  conceptualmente como una tupla que contiene un identificador, un valor, un
  identificador de supervisor y un contador de dependientes: (ident, val,
  identSup, NumDepend).

  Se distinguen dos tipos de elementos: 'independientes' (ident, val, -,
  NumDepend), y 'dependientes' (ident, val, identSup, NumDepend), donde
  'identSup' es el identificador de otro elemento ya existente en la misma
  colección.

  Esta colección cuenta con las siguientes restricciones. Primero, no pueden
  existir dos elementos con el mismo 'ident'. La colección se mantiene siempre
  ordenada crecientemente según este 'ident'. Ninguno de sus elementos puede
  depender de sí mismo (sus 'id's deben ser distinto de sus 'identSup's).
  Finalmente, el campo 'NumDepend' de un elemento 'A' siempre almacena el número
  total de elementos en la colección que dependen directamente de 'A'.

  Respecto al coste de esta implementación, las operaciones 'crear', 'tamanyo',
  'esVacia' y todas las del iterador tienen un coste constante O(1). Las
  operaciones que implican búsqueda, inserción o borrado ('existe',
  'existeDependiente', 'existeIndependiente', 'anadirIndependiente',
  'anadirDependiente', 'hacerDependiente', 'hacerIndependiente', 'actualizarVal',
  'obtenerVal', 'obtenerSupervisor', 'obtenerNumDependientes', 'borrar' y
  'obtenerInfo') tienen un coste que depende de la estructura interna (ver
  detalles en la parte privada de implementación). El coste en memoria es O(N),
  donde N es el número de elementos.

  A los parámetros formales genéricos se les exigen ciertos operadores.
  Al parámetro 'ident' le exigimos estar dotado de los operadores de comparación
  de igualdad (==) y de anterioridad (<), que definen un orden total necesario
  para la ordenación y búsqueda. Al parámetro 'val' se le exige el operador de
  copia/asignación (=) para poder almacenar y devolver valores.
*/
template <typename ident, typename val> struct colecInterdep;

/* Crea una colección vacía, sin elementos.
 */
template <typename ident, typename val>
void crear(colecInterdep<ident, val> &c);

/* Devuelve el número de elementos que hay en la colección c.
 */
template <typename ident, typename val>
unsigned int tamanyo(const colecInterdep<ident, val> &c);

/* Devuelve true si y solo si c no contiene ningún elemento, false en caso
 * contrario.
 */
template <typename ident, typename val>
bool esVacia(const colecInterdep<ident, val> &c);

/* Devuelve true si existe un elemento en la coleccion c con identificador 'id',
 * false en caso contrario.
 */
template <typename ident, typename val>
bool existe(const colecInterdep<ident, val> &c, const ident &id);

/* Devuelve true si existe un elemento en c con identificador 'id' y este es
 * dependiente, false en caso contrario.
 */
template <typename ident, typename val>
bool existeDependiente(const colecInterdep<ident, val> &c, const ident &id);

/* Devuelve true si existe un elemento en c con identificador 'id' y este es
 * independiente, false en caso contrario.
 */
template <typename ident, typename val>
bool existeIndependiente(const colecInterdep<ident, val> &c, const ident &id);

/* En el caso de que no exista un elemento con 'id', añade un nuevo elemento
  independiente (id, v, -, 0) a la colección 'c' manteniéndola ordenada. Si ya
  existe 'id', no modifica 'c'.
*/
template <typename ident, typename val>
void anadirIndependiente(colecInterdep<ident, val> &c, const ident &id,
                         const val &v);

/* En el caso de que no exista 'id', sí exista 'super', y 'id' != 'super', añade
 un nuevo elemento dependiente (id, v, super, 0) a la colección 'c'
 manteniéndola ordenada e incrementa en 1 el 'NumDepend' del supervisor 'super'.
 Si 'id' ya existe, 'super' no existe, o 'id' == 'super', no modifica 'c'.
*/
template <typename ident, typename val>
void anadirDependiente(colecInterdep<ident, val> &c, const ident &id,
                       const val &v, const ident &super);

/* En el caso de que existan 'id' y 'super', y 'id' != 'super', modifica 'id'
 para que dependa de 'super'. Si 'id' ya era dependiente, decrementa en 1 la
 contabilidad de su antiguo supervisor. E incrementa en 1 el 'NumDepend' de
 'super'.
*/
template <typename ident, typename val>
void hacerDependiente(colecInterdep<ident, val> &c, const ident &id,
                      const ident &super);

/* En el caso de que exista 'id' y sea dependiente, lo convierte en
 independiente. Decrementa en 1 el 'NumDepend' de su antiguo supervisor.Si 'id'
 no existe o ya era independiente, devuelve la colección sin cambios.
*/
template <typename ident, typename val>
void hacerIndependiente(colecInterdep<ident, val> &c, const ident &id);

/* En el caso de que exista un elemento con 'id', actualiza su campo 'valor' con
 * el 'nuevo' valor y devuelve true. Si 'id' no existe, devuelve false.
 */
template <typename ident, typename val>
bool actualizarVal(colecInterdep<ident, val> &c, const ident &id,
                   const val &nuevo);

/* En el caso de que exista un elemento con 'id', carga en 'valO' su valor y
 * devuelve true. Si 'id' no existe, no modifica 'valO' y devuelve false.
 */
template <typename ident, typename val>
bool obtenerVal(const colecInterdep<ident, val> &c, const ident &id, val &valO);

/* En el caso de que exista 'id' y sea dependiente, carga en 'idO' el
 identificador de su supervisor y devuelve true. Si 'id' no existe o es
 independiente, no modifica 'idO' y devuelve false.
*/
template <typename ident, typename val>
bool obtenerSupervisor(const colecInterdep<ident, val> &c, const ident &id,
                       ident &idO);

/* En el caso de que exista un elemento con 'id', carga en 'NumDepO' su número
 de dependientes directos y devuelve true. Si 'id' no existe, no modifica
 'NumDepO' y devuelve false.
*/
template <typename ident, typename val>
bool obtenerNumDependientes(const colecInterdep<ident, val> &c, const ident &id,
                            unsigned int &NumDepO);

/* En el caso de que exista 'id' y no tenga dependientes ('NumDepend' sea 0), lo
 elimina de la colección respetando el orden. Si 'id' era dependiente, actualiza
 la contabilidad de su supervisor quitando 1 en 'NumDepend'. Si 'id' no existe o
 tiene dependientes, no modifica 'c'.
*/
template <typename ident, typename val>
void borrar(colecInterdep<ident, val> &c, const ident &id);

// --- OPERACIONES DEL ITERADOR ---

/* Prepara el iterador para que el siguiente elemento a visitar sea el primero
 de la colección (el de 'ident' menor).
*/
template <typename ident, typename val>
void iniciarIterador(colecInterdep<ident, val> &c);

/* Devuelve true si queda algún elemento por visitar, false en caso contrario.
 */
template <typename ident, typename val>
bool existeSiguiente(const colecInterdep<ident, val> &c);

/* Si existe un elemento pendiente de visitar, carga en 'sig' su 'ident' y
  devuelve true. Si no quedan elementos por visitar, devuelve false.
*/
template <typename ident, typename val>
bool siguienteIdent(const colecInterdep<ident, val> &c, ident &sig);

/* Si existe un elemento pendiente de visitar, carga en 'sig' su 'valor' y
  devuelve true. Si no quedan elementos por visitar, devuelve false.
*/
template <typename ident, typename val>
bool siguienteVal(const colecInterdep<ident, val> &c, val &sig);

/* Si existe un elemento pendiente de visitar, devuelve true si este es
  dependiente, o false si es independiente. Si no quedan elementos, devuelve
  false.
*/
template <typename ident, typename val>
bool siguienteDependiente(const colecInterdep<ident, val> &c);

/* Si existe un elemento pendiente de visitar y es dependiente, carga en 'sig'
  el 'ident' de su supervisor y devuelve true. Si no quedan elementos o el
  actual es independiente, devuelve false.
*/
template <typename ident, typename val>
bool siguienteSuperior(const colecInterdep<ident, val> &c, ident &sig);

/* Si existe un elemento pendiente de visitar, carga en 'num' su 'NumDepend'y
  devuelve true. Si no quedan elementos por visitar, devuelve false.
*/
template <typename ident, typename val>
bool siguienteNumDependientes(const colecInterdep<ident, val> &c, int &num);

/* Si existe un elemento pendiente de visitar, avanza el iterador al siguiente
elemento y devuelve true. Si no quedan elementos (el iterador está al final), no
avanza y devuelve false.
*/
template <typename ident, typename val>
bool avanza(colecInterdep<ident, val> &c);

/* Si existe un elemento con 'id', carga en los parámetros de salida 'valO' con
 su 'valor', 'depen' asignandole true si es dependiente y false en caso
 contrario, modificanco 'idO' solo si es dependiente y 'NumDepO' con su
 'NumDepend' y devuelve true. Si 'id' no existe, no modifica ninguno de los
 parámetros y devuelve false.
*/
template <typename ident, typename val>
bool obtenerInfo(const colecInterdep<ident, val> &c, const ident &id, val &valO,
                 bool &depen, ident &idO, unsigned int &NumDepO);

/* Funcion auxiliar de la parte privada de la estructura colecInterdep. Se
 * utiliza para implementar las funciones 'anadirDependiente' y
 * 'anadirIndependiente'. Su implementacion se especifica más adelante*/
template <typename ident, typename val>
void anadirRec(typename colecInterdep<ident, val>::Nodo *&p, const ident &id,
               const val &v, bool &anadido,
               typename colecInterdep<ident, val>::Nodo *ptrSuper);
/* Funcion auxiliar de la parte privada de la estructura colecInterdep. Se
 * utiliza para implementar las funciones donde sea necesaria busqueda del nodo.
 * En ptrId devuelve el puntero al elemento 'id'. Su implementacion se
 * especifica más adelante*/
template <typename ident, typename val>
void encontrarRec(typename colecInterdep<ident, val>::Nodo *p, const ident &id,
                  typename colecInterdep<ident, val>::Nodo *&ptrId);

/* Funcion auxiliar de la parte privada de la estructura colecInterdep. Se
 * utiliza para implementar la funcion 'borrarRec'. Su implementacion se
 * especifica más adelante*/
template <typename ident, typename val>
void borrarMax(typename colecInterdep<ident, val>::Nodo *&p, ident &id, val &v,
               typename colecInterdep<ident, val>::Nodo *&identSup,
               unsigned int &numDepend);

/* Funcion auxiliar de la parte privada de la estructura colecInterdep. Se
 * utiliza para implementar la funcion 'borrar'. Su implementacion se
 * especifica más adelante*/
template <typename ident, typename val>
void borrarRec(typename colecInterdep<ident, val>::Nodo *&p, const ident &id,
               bool &borrado);

/* Funcion auxiliar de la parte privada de la estructura colecInterdep. Se
 * utiliza para optimizar 'anadirDependiente'. Realiza una búsqueda dual
 * optimizada: recorre el ABB buscando simultáneamente el supervisor 'super'
 * (que debe existir) y la posición para insertar 'id' (que no debe existir).
 * Cuando ambos elementos comparten caminos en el árbol, se recorre solo una vez
 * ese camino compartido. Al divergir los caminos, delega en 'encontrarRec' y
 * 'anadirRec' para búsquedas/inserciones independientes. El parámetro
 * 'idMenorQueSuper' indica la relación entre id y super para optimizar las
 * decisiones de navegación. Su implementacion se especifica más adelante.
 */
template<typename ident, typename val> void anadirRecColateral(typename colecInterdep<ident,val>::Nodo *&p, const ident& id, const val& v, const ident& super, typename colecInterdep<ident,val>::Nodo*& ptrSuper, bool& anadido, bool idMenorQueSuper);

/* Funcion auxiliar de la parte privada de la estructura colecInterdep. Se
 * utiliza para optimizar 'hacerDependiente'. Realiza una búsqueda dual
 * optimizada de dos elementos que deben existir: recorre el ABB buscando
 * simultáneamente 'id' y 'super'. Cuando ambos elementos comparten caminos en el
 * árbol, se recorre solo una vez ese camino compartido. Al divergir los caminos,
 * delega en 'encontrarRec' para búsquedas independientes. Devuelve en ptrId y
 * ptrSuper los punteros a ambos nodos, o nullptr si alguno no existe. El
 * parámetro 'idMenorQueSuper' indica la relación entre id y super para optimizar
 * las decisiones de navegación. Su implementacion se especifica más adelante.
 */
template<typename ident, typename val> void busquedaRecColateral(typename colecInterdep<ident,val>::Nodo *&p, const ident& id, const ident& super, typename colecInterdep<ident,val>::Nodo*& ptrId, typename colecInterdep<ident,val>::Nodo*& ptrSuper, bool idMenorQueSuper);

// FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)

// DECLARACION DEL TAD GENERICO colecInterdep

template <typename ident, typename val> struct colecInterdep {
  friend void crear<ident, val>(colecInterdep<ident, val> &c);
  friend bool esVacia<ident, val>(const colecInterdep<ident, val> &c);
  friend bool existe<ident, val>(const colecInterdep<ident, val> &c,
                                 const ident &id);
  friend unsigned int tamanyo<ident, val>(const colecInterdep<ident, val> &c);
  friend bool existeDependiente<ident, val>(const colecInterdep<ident, val> &c,
                                            const ident &id);
  friend bool
  existeIndependiente<ident, val>(const colecInterdep<ident, val> &c,
                                  const ident &id);
  friend void anadirIndependiente<ident, val>(colecInterdep<ident, val> &c,
                                              const ident &id, const val &v);
  friend void anadirDependiente<ident, val>(colecInterdep<ident, val> &c,
                                            const ident &id, const val &v,
                                            const ident &super);
  friend void hacerDependiente<ident, val>(colecInterdep<ident, val> &c,
                                           const ident &id, const ident &super);
  friend void hacerIndependiente<ident, val>(colecInterdep<ident, val> &c,
                                             const ident &id);
  friend bool actualizarVal<ident, val>(colecInterdep<ident, val> &c,
                                        const ident &id, const val &nuevo);
  friend bool obtenerVal<ident, val>(const colecInterdep<ident, val> &c,
                                     const ident &id, val &valO);
  friend bool obtenerSupervisor<ident, val>(const colecInterdep<ident, val> &c,
                                            const ident &id, ident &idO);
  friend bool
  obtenerNumDependientes<ident, val>(const colecInterdep<ident, val> &c,
                                     const ident &id, unsigned int &NumDepO);
  friend void borrar<ident, val>(colecInterdep<ident, val> &c, const ident &id);
  friend void iniciarIterador<ident, val>(colecInterdep<ident, val> &c);
  friend bool existeSiguiente<ident, val>(const colecInterdep<ident, val> &c);
  friend bool siguienteIdent<ident, val>(const colecInterdep<ident, val> &c,
                                         ident &sig);
  friend bool siguienteVal<ident, val>(const colecInterdep<ident, val> &c,
                                       val &sig);
  friend bool
  siguienteDependiente<ident, val>(const colecInterdep<ident, val> &c);
  friend bool siguienteSuperior<ident, val>(const colecInterdep<ident, val> &c,
                                            ident &sig);
  friend bool
  siguienteNumDependientes<ident, val>(const colecInterdep<ident, val> &c,
                                       int &num);
  friend bool avanza<ident, val>(colecInterdep<ident, val> &c);
  friend bool obtenerInfo<ident, val>(const colecInterdep<ident, val> &c,
                                      const ident &id, val &valO, bool &depen,
                                      ident &idO, unsigned int &NumDepO);
                                  


private:
  /*
  IMPLEMENTACIÓN:
  
  La implementación de este TAD se basa en un Árbol Binario de Búsqueda (ABB)
  ordenado por el campo 'id' de los nodos. La estructura 'colecInterdep' almacena
  un puntero 'raiz' al nodo raiz del árbol, siendo 'nullptr' si la colección está
  vacía.

  Se incluye un contador 'numElem' para el total de elementos. Esta decisión de
  diseño es crucial para que las operaciones 'tamanyo' y 'esVacia' tengan un
  coste computacional O(1). Se usa una pila de punteros 'iter' para gestionar el
  estado del iterador interno, apuntando al siguiente nodo a visitar o a
  'nullptr' si la iteración ha concluido.

  El 'struct Nodo' define la estructura interna de cada elemento. Contiene el
  'id' (que actúa como clave de ordenación en el ABB), el 'valor', un puntero
  'identSup' que apunta directamente al nodo supervisor (o es 'nullptr' si es
  independiente) para reducir el coste computacional de borrar o hacerIndependiente
  al no tener que volver a buscar al padre para decrementar su numDependientes, el
  contador 'numDepend', y dos punteros a nodos "hijoDer" y "hijoIzq" que almacenan
  respectivamente el elemento mayor al actual y el menor.
  
  ANÁLISIS DE COSTES:
  
  Las operaciones sobre el ABB tienen coste O(h), donde h es la altura del árbol:
  
  - Operaciones con búsqueda simple ('existe', 'existeDependiente',
    'existeIndependiente', 'anadirIndependiente', 'actualizarVal', 'obtenerVal',
    'obtenerSupervisor', 'obtenerNumDependientes', 'borrar', 'obtenerInfo'):
    coste O(h).
    
  - Operaciones con búsqueda dual optimizada ('anadirDependiente',
    'hacerDependiente'): utilizan funciones auxiliares colaterales que buscan dos
    elementos simultáneamente aprovechando caminos compartidos en el ABB. Coste
    O(h) en el mejor caso (ambos elementos comparten gran parte del camino) y
    O(2h) = O(h) en el peor caso (caminos divergen desde la raíz).
    
  En el peor caso (ABB degenerado, similar a una lista enlazada ordenada): h = N → O(N).
  En el mejor caso (ABB perfectamente balanceado): h = log(N) → O(log N).
  */

  struct Nodo {
    ident id;
    val valor;
    Nodo *identSup = nullptr;
    unsigned int numDepend = 0;
    Nodo *hijoIzq;
    Nodo *hijoDer;
  };

  friend void anadirRec<ident, val>(Nodo *&p, const ident &id, const val &v,
                                    bool &anadido, Nodo *ptrSuper);
  friend void encontrarRec<ident, val>(Nodo *p, const ident &id, Nodo *&ptrId);
  friend void borrarRec<ident, val>(Nodo *&p, const ident &id, bool &borrado);
  friend void borrarMax<ident, val>(Nodo *&p, ident &id, val &v,
                                    Nodo *&identSup, unsigned int &numDepend);
  
  friend void anadirRecColateral<ident,val>(Nodo *&p, const ident& id, const val& v, const ident& super, Nodo*& ptrSuper, bool& anadido, bool idMenorQueSuper);
  
  friend void busquedaRecColateral<ident,val>(Nodo *&p, const ident& id, const ident& super, Nodo*& ptrId, Nodo*& ptrSuper, bool idMenorQueSuper);

  Nodo *raiz;           // Puntero a la raiz del árbol
  unsigned int numElem; // Número total de elementos
  Pila<Nodo *> iter;    // implementamos el iterador con pila
};

// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colecInterdep

/* Crea una colección vacía, sin elementos.
   Inicializa la colección estableciendo el puntero 'raiz' a 'nullptr'.
   Inicializa una pila vacia de iterador. El contador de elementos 'numElem' se
   inicializa a 0 para reflejar que la colección está vacía.
*/
template <typename ident, typename val>
void crear(colecInterdep<ident, val> &c) {
  c.raiz = nullptr;
  c.numElem = 0;
  crearVacia(c.iter);
}

/* Devuelve el número de elementos que hay en la colección c.
   La operación devuelve directamente el valor del contador 'numElem'.
   Gracias a mantener este contador actualizado en las operaciones de inserción
   y borrado, esta consulta tiene un coste O(1).
*/
template <typename ident, typename val>
unsigned int tamanyo(const colecInterdep<ident, val> &c) {
  return c.numElem;
}

/* Devuelve true si y solo si c no contiene ningún elemento, false en caso
   contrario. La eficiencia de esta operación es O(1) dado que la estructura
   mantiene un contador 'numElem' con el total de elementos. Por lo tanto, la
   función simplemente comprueba si dicho contador es igual a 0.
*/
template <typename ident, typename val>
bool esVacia(const colecInterdep<ident, val> &c) {
  return (c.numElem == 0);
}

/* Devuelve true si existe un elemento en la coleccion c con identificador 'id',
   false en caso contrario. Se utiliza la funcion auxiliar "encontrarRec"
   devolviendo true solo si 'aux' no es nulo y 'aux->id == id'.
*/
template <typename ident, typename val>
bool existe(const colecInterdep<ident, val> &c, const ident &id) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    return true;
  }
  return false;
}

// Recorre el árbol recursivamente in orden, si encuentra el nodo con id 'id'
// devuelve en ptrId el puntero a nodo con id "id". Si recorre todo el árbol sin
// haber encontrado el elemento con id "id" devuelve el puntero vacio en
// "ptrId".
template <typename ident, typename val>
void encontrarRec(typename colecInterdep<ident, val>::Nodo *p, const ident &id,
                  typename colecInterdep<ident, val>::Nodo *&ptrId) {
  if (p == nullptr) {
    ptrId = nullptr;
  } else {
    if (id < p->id) {
      encontrarRec<ident, val>(p->hijoIzq, id, ptrId);
    } else if (id == p->id) {
      ptrId = p;
    } else if (id > p->id) {
      encontrarRec<ident, val>(p->hijoDer, id, ptrId);
    }
  }
}

/* Devuelve true si existe un elemento en c con identificador 'id' y este es
   dependiente (tiene un supervisor), false en caso contrario. Se utiliza la
   funcion auxiliar "encontrarRec" para encontrar el nodo con id "id". Tras
   encontrar el nodo (si 'ptrId != nullptr
   && ptrId->id == id'), se añade una comprobación adicional para verificar que
   el puntero al supervisor, 'ptrId->identSup', sea distinto de 'nullptr'.
*/
template <typename ident, typename val>
bool existeDependiente(const colecInterdep<ident, val> &c, const ident &id) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    if (ptrId->identSup != nullptr) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

/* Devuelve true si existe un elemento en c con identificador 'id' y este es
   independiente (no tiene supervisor), false en caso contrario. Se utiliza la
   funcion auxiliar "encontrarRec" para encontrar el nodo con id "id".. Si se
   encuentra, se comprueba que su puntero supervisor 'ptrId->identSup' sea igual
   a 'nullptr', lo que define a un nodo como independiente.
*/
template <typename ident, typename val>
bool existeIndependiente(const colecInterdep<ident, val> &c, const ident &id) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    if (ptrId->identSup == nullptr) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

/* Añade un nodo con identificador 'id' y valor 'v' al árbol. La función busca
   recursivamente la posición donde insertarlo: si el hueco está vacío crea un
   nodo nuevo e inicializa sus campos; si el identificador ya existe, marca
   'anadido' como false; y si no, sigue buscando por el hijo izquierdo o
   derecho según corresponda. El parámetro 'ptrSuper' se guarda como supervisor
   del nuevo nodo.
*/
template <typename ident, typename val>
void anadirRec(typename colecInterdep<ident, val>::Nodo *&p, const ident &id,
               const val &v, bool &anadido,
               typename colecInterdep<ident, val>::Nodo *ptrSuper) {
  if (p == nullptr) {
    p = new typename colecInterdep<ident, val>::Nodo;
    p->id = id;
    p->valor = v;
    p->identSup = ptrSuper;
    p->numDepend = 0;
    p->hijoIzq = nullptr;
    p->hijoDer = nullptr;
    anadido = true;
  } else {
    if (id < p->id) {
      anadirRec<ident, val>(p->hijoIzq, id, v, anadido, ptrSuper);
    } else if (id == p->id) {
      anadido = false;
    } else if (id > p->id) {
      anadirRec<ident, val>(p->hijoDer, id, v, anadido, ptrSuper);
    }
  }
}

/* Añade a la colección un nodo independiente (sin supervisor) con
   identificador 'id' y valor 'v'. Si la colección está vacía, crea la
   raíz directamente. En caso contrario, llama a 'anadirRec' pasando un
   supervisor nulo para insertarlo como nodo independiente. Si la
   inserción tiene éxito, aumenta el número de elementos.
*/
template <typename ident, typename val>
void anadirIndependiente(colecInterdep<ident, val> &c, const ident &id,
                         const val &v) {
  if (c.numElem == 0) {
    typename colecInterdep<ident, val>::Nodo *aux =
        new typename colecInterdep<ident, val>::Nodo;
    aux->id = id;
    aux->valor = v;
    aux->identSup = nullptr;
    aux->numDepend = 0;
    aux->hijoIzq = nullptr;
    aux->hijoDer = nullptr;
    c.raiz = aux;
    c.numElem++;
  } else {
    bool anadido;
    typename colecInterdep<ident, val>::Nodo *ptrSuper = nullptr;
    anadirRec<ident, val>(c.raiz, id, v, anadido, ptrSuper);
    if (anadido) {
      c.numElem++;
    }
  }
}

/* Añade a la colección un nodo dependiente con identificador 'id' y valor 'v'.
   Primero busca el nodo del supervisor 'super' usando 'encontrarRec'. Si
   existe, intenta insertar el nuevo nodo mediante 'anadirRec', pasándole el
   puntero del supervisor para que quede registrado como tal. Si la inserción
   tiene éxito, aumenta el número total de elementos y el contador de
   dependientes del supervisor.
*/
template<typename ident, typename val> 
void anadirDependiente(colecInterdep<ident, val>& c, const ident& id, const val& v, const ident& super){
  if (id == super || c.raiz == nullptr) {
    return;
  }
  typename colecInterdep<ident, val>::Nodo* ptrSuper = nullptr;
  bool anadido = false;
  anadirRecColateral<ident,val>(c.raiz, id, v, super, ptrSuper, anadido, id < super);
  if (anadido) {
    c.numElem++;
  }
}



/* Implementacion unificada de la busqueda e insercion dual optimizada.
   Recorre el ABB buscando simultaneamente el supervisor 'super' y la posicion
   para insertar 'id'. El parametro idMenorQueSuper indica si id < super (true)
   o id > super (false), permitiendo optimizar las decisiones en cada nodo.
   Al saber la relacion entre id y super (id < super o id > super),
   podemos predecir en que subarboles estaran ambos elementos, evitando recorrer
   el arbol dos veces por separado. Cuando ambos elementos siguen el mismo camino,
   continuamos con la busqueda dual. Cuando los caminos se separan, delegamos en
   funciones de busqueda e insercion individuales para terminar el proceso.
*/
template<typename ident, typename val> 
void anadirRecColateral(typename colecInterdep<ident,val>::Nodo *&p, const ident& id, const val& v, const ident& super, typename colecInterdep<ident,val>::Nodo*& ptrSuper, bool& anadido, bool idMenorQueSuper){
  if (p == nullptr){
    anadido = false;
    return;
  }
  // Segun la relacion entre id y super, determinamos a que subarboles iran:
  // - hijoAmbos: subarbol donde van ambos cuando comparten el mismo camino
  // - hijoId: subarbol donde ira 'id' cuando los caminos se separan
  // - hijoSuper: subarbol donde ira 'super' cuando los caminos se separan
  // Si id < super: ambos juntos van a la derecha, separados id->izq y super->der
  // Si id > super: ambos juntos van a la izquierda, separados id->der y super->izq
  typename colecInterdep<ident,val>::Nodo *&hijoAmbos = idMenorQueSuper ? p->hijoDer : p->hijoIzq;
  typename colecInterdep<ident,val>::Nodo *&hijoId = idMenorQueSuper ? p->hijoIzq : p->hijoDer;
  typename colecInterdep<ident,val>::Nodo *&hijoSuper = idMenorQueSuper ? p->hijoDer : p->hijoIzq;
  bool idEnAmbos = idMenorQueSuper ? (id > p->id) : (id < p->id);
  
  if(idEnAmbos){
    // Ambos elementos van por el mismo camino, continuamos la busqueda dual
    anadirRecColateral<ident,val>(hijoAmbos, id, v, super, ptrSuper, anadido, idMenorQueSuper);
  }else if(id == p->id){
    //El elemento ya existe en el arbol, no insertamos duplicados
    anadido = false;
  }else{
    // El elemento 'id' ira por hijoId, verifiquemos donde ira 'super'
    bool superEnMismoLado = idMenorQueSuper ? (super < p->id) : (super > p->id);
    
    if (superEnMismoLado){
      //Ambos siguen en el mismo subarbol, continuamos busqueda dual
      anadirRecColateral<ident,val>(hijoId, id, v, super, ptrSuper, anadido, idMenorQueSuper);
    }else if (super != p->id){
      // Los caminos se separan: id va a hijoId y super va a hijoSuper
      //Buscamos super en su subarbol, luego insertamos id en el suyo
      encontrarRec<ident,val>(hijoSuper, super, ptrSuper);
      if(ptrSuper!=nullptr){
        anadirRec<ident, val>(hijoId, id, v, anadido, ptrSuper);
        if(anadido){
          ptrSuper->numDepend++;
        }
      }
    }else{
      //Hemos encontrado el supervisor en el nodo actual
      //Insertamos id como dependiente en hijoId
      ptrSuper = p;
      anadirRec<ident, val>(hijoId, id, v, anadido, ptrSuper);
      if(anadido){
        ptrSuper->numDepend++;
      }
    }
  }
}




/* Implementacion unificada de la busqueda dual optimizada. Recorre el ABB
   buscando simultaneamente 'id' y 'super'. El parametro idMenorQueSuper indica
   si id < super (true) o id > super (false), optimizando las decisiones.
   Similar a anadirRecColateral, aprovecha el conocimiento de la
   relacion entre id y super para recorrer el arbol una sola vez cuando ambos
   elementos comparten camino. Cuando los caminos divergen, delega en encontrarRec
   para buscar cada elemento por separado.
*/
template<typename ident, typename val> 
void busquedaRecColateral(typename colecInterdep<ident,val>::Nodo *&p, const ident& id, const ident& super, typename colecInterdep<ident,val>::Nodo*& ptrId, typename colecInterdep<ident,val>::Nodo*& ptrSuper, bool idMenorQueSuper){
  if (p == nullptr || id == super){
    ptrId = nullptr;
    ptrSuper = nullptr;
    return;
  }
  // Segun la relacion entre id y super, determinamos a que subarboles iran:
  // - hijoAmbos: subarbol donde estan ambos cuando comparten el mismo camino
  // - hijoId: subarbol donde esta 'id' cuando los caminos se separan
  // - hijoSuper: subarbol donde esta 'super' cuando los caminos se separan
  // La logica es identica a anadirRecColateral para mantener consistencia
  typename colecInterdep<ident,val>::Nodo *&hijoAmbos = idMenorQueSuper ? p->hijoDer : p->hijoIzq;
  typename colecInterdep<ident,val>::Nodo *&hijoId = idMenorQueSuper ? p->hijoIzq : p->hijoDer;
  typename colecInterdep<ident,val>::Nodo *&hijoSuper = idMenorQueSuper ? p->hijoDer : p->hijoIzq;
  bool idEnAmbos = idMenorQueSuper ? (id > p->id) : (id < p->id);
  
  if(idEnAmbos){
    // Ambos elementos van por el mismo camino, continuamos la busqueda dual
    busquedaRecColateral<ident,val>(hijoAmbos, id, super, ptrId, ptrSuper, idMenorQueSuper);
  }else if(id == p->id){
    //Hemos encontrado 'id', ahora solo falta buscar 'super' en hijoSuper
    ptrId = p;
    encontrarRec<ident,val>(hijoSuper, super, ptrSuper);
  }else{
    //El elemento 'id' esta en hijoId, verifiquemos donde esta 'super'
    bool superEnMismoLado = idMenorQueSuper ? (super < p->id) : (super > p->id);
    
    if (superEnMismoLado){
      //Ambos siguen en el mismo subarbol, continuamos busqueda dual
      busquedaRecColateral<ident,val>(hijoId, id, super, ptrId, ptrSuper, idMenorQueSuper);
    }else if (super != p->id){
      // Los caminos se separan: id esta en hijoId y super esta en hijoSuper
      //Buscamos cada uno por separado en su respectivo subarbol
      encontrarRec<ident,val>(hijoId, id, ptrId);
      encontrarRec<ident,val>(hijoSuper, super, ptrSuper);
    }else{
      //Hemos encontrado el supervisor en el nodo actual
      //Solo falta buscar 'id' en hijoId
      ptrSuper = p;
      encontrarRec<ident,val>(hijoId, id, ptrId);
    }
  }
}



/* Hace que el nodo con identificador 'id' pase a depender del nodo 'super'.
   Primero comprueba que 'id' y 'super' son distintos y busca ambos nodos con
   'encontrarRec'. Si alguno no existe, no se realiza nada. Si existen, y 'id'
   ya tenía un supervisor, se decrementa el contador de dependientes del
   supervisor anterior. A continuación se asigna el nuevo supervisor y se
   incrementa el número de dependientes de 'super'.
*/
template <typename ident, typename val>
void hacerDependiente(colecInterdep<ident, val> &c, const ident &id,
                      const ident &super) {
  if (id != super && c.raiz != nullptr) {
    typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
    typename colecInterdep<ident, val>::Nodo *ptrSuper = nullptr;
    
    // Búsqueda colateral optimizada
    busquedaRecColateral<ident,val>(c.raiz, id, super, ptrId, ptrSuper, id < super);
    
    // Si ambos existen, realizar el cambio de dependencia
    if (ptrId != nullptr && ptrSuper != nullptr) {
      if (ptrId->identSup != nullptr) {
        ptrId->identSup->numDepend--;
      }
      ptrId->identSup = ptrSuper;
      ptrSuper->numDepend++;
    }
  }
}

// /*En el caso de que exista 'id' y sea dependiente, lo convierte en
// independiente. Decrementa en 1 el 'NumDepend' de su antiguo supervisor.
//    Buscamos el nodo con 'id' usando la función auxiliar 'encontrarRec'. Si se
//    encuentra y se confirma que es dependiente ('aux->identSup != nullptr'),
//    se accede a su supervisor ('aux->identSup') y se decrementa 'numDepend'.
//    Para despues establecer 'aux->identSup = nullptr' para marcarlo como
//    independiente. Si no se encuentra o ya era independiente, devuelve
//    'false'.
// */
template <typename ident, typename val>
void hacerIndependiente(colecInterdep<ident, val> &c, const ident &id) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    if (ptrId->identSup != nullptr) {
      ptrId->identSup->numDepend--;
      ptrId->identSup = nullptr;
    }
  }
}

// /* En el caso de que exista un elemento con 'id', actualiza su campo 'valor'
// con el 'nuevo' valor y devuelve true. Si 'id' no existe, devuelve false.
//    Busca el nodo con 'id' ('aux'). Si lo encuentra, se sobrescribe su campo
//    'valor' con el 'nuevo' valor y se devuelve 'true'. Si no existe el nodo
//    'id' devuelve false.
// */
template <typename ident, typename val>
bool actualizarVal(colecInterdep<ident, val> &c, const ident &id,
                   const val &nuevo) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    ptrId->valor = nuevo;
    return true;
  }
  return false;
}

// /*En el caso de que exista un elemento con 'id', carga en 'valO' su valor y
// devuelve true. Si 'id' no existe, no modifica 'valO' y devuelve false.
//    Se busca el nodo con 'id'. Si lo encuentra, se le asigna el valor
//    'valO = aux->valor' y se devuelve 'true'. En caso contrario, 'false'.
// */
template <typename ident, typename val>
bool obtenerVal(const colecInterdep<ident, val> &c, const ident &id,
                val &valO) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    valO = ptrId->valor;
    return true;
  }
  return false;
}

// /* En el caso de que exista 'id' y sea dependiente, carga en 'idO' el
// identificador de su supervisor y devuelve true. Si 'id' no existe o es
//  independiente, no modifica 'idO' y devuelve false.
//    Se busca el nodo con 'id'. Si lo encuentra y se confirma que es
//    dependiente, se asigna el identificador del supervisor 'idO =
//    aux->identSup->id' y se devuelve 'true'. Si no se encuentra o es
//    independiente, devuelve 'false'.
// */
template <typename ident, typename val>
bool obtenerSupervisor(const colecInterdep<ident, val> &c, const ident &id,
                       ident &idO) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr && ptrId->identSup != nullptr) {
    idO = ptrId->identSup->id;
    return true;
  }
  return false;
}

// /* En el caso de que exista un elemento con 'id', carga en 'NumDepO' su
// número de dependientes directos y devuelve true. Si 'id' no existe, no
// modifica
//  'NumDepO' y devuelve false.
//    Se busca el nodo con 'id'. Si se encuentra, se asigna el valor
//    'NumDepO = aux->numDepend' y se devuelve 'true'. En caso contrario,
//    devolveremos 'false'.
// */
template <typename ident, typename val>
bool obtenerNumDependientes(const colecInterdep<ident, val> &c, const ident &id,
                            unsigned int &NumDepO) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    NumDepO = ptrId->numDepend;
    return true;
  }
  return false;
}

/* Elimina de la colección el nodo con identificador 'id'. Llama a 'borrarRec'
   para localizarlo y realizar la eliminación. Si realmente se borra un nodo,
   se decrementa el número total de elementos de la colección.
*/
template <typename ident, typename val>
void borrar(colecInterdep<ident, val> &c, const ident &id) {
  bool borrado = false;
  borrarRec<ident, val>(c.raiz, id, borrado);
  if (borrado) {
    c.numElem--;
  }
}

/* Busca y elimina recursivamente el nodo con identificador 'id'. Si el nodo se
   encuentra, ajusta primero la contabilidad del supervisor (si tenía) y luego
   realiza la eliminación según el caso: sin hijos, con un hijo o con dos hijos.
   En el caso de dos hijos, delega en 'borrarMax' para sustituir el nodo por su
   predecesor inmediato. Marca 'borrado' como true cuando la operación se
   realiza.
*/
template <typename ident, typename val>
void borrarRec(typename colecInterdep<ident, val>::Nodo *&p, const ident &id,
               bool &borrado) {
  if (p == nullptr) {
    borrado = false;
  } else {
    if (id < p->id) {
      borrarRec<ident, val>(p->hijoIzq, id, borrado);
    } else if (id > p->id) {
      borrarRec<ident, val>(p->hijoDer, id, borrado);
    } else {
      borrado = true;
      typename colecInterdep<ident, val>::Nodo *aux = p;
      if (aux->identSup != nullptr) {
        aux->identSup->numDepend--;
      }
      if (p->hijoIzq == nullptr) {
        p = p->hijoDer;
        delete (aux);
      } else if (p->hijoDer == nullptr) {
        p = p->hijoIzq;
        delete (aux);
      } else {
        borrarMax<ident, val>(p->hijoIzq, p->id, p->valor, p->identSup,
                              p->numDepend);
      }
    }
  }
}

/* Obtiene y elimina el nodo con mayor identificador dentro del subárbol
   apuntado por 'p'. Copia sus datos ('id', 'v', 'identSup', 'numDepend') en
   los parámetros de salida y reemplaza el nodo eliminado por su hijo izquierdo.
   Se usa como apoyo en la eliminación de nodos con dos hijos.
*/
template <typename ident, typename val>
void borrarMax(typename colecInterdep<ident, val>::Nodo *&p, ident &id, val &v,
               typename colecInterdep<ident, val>::Nodo *&identSup,
               unsigned int &numDepend) {
  if (p->hijoDer == nullptr) {
    id = p->id;
    v = p->valor;
    identSup = p->identSup;
    numDepend = p->numDepend;
    typename colecInterdep<ident, val>::Nodo *aux = p;
    p = p->hijoIzq;
    delete aux;
  } else {
    borrarMax<ident, val>(p->hijoDer, id, v, identSup, numDepend);
  }
}
//

// // --- IMPLEMENTACION OPERACIONES ITERADOR ---

/* Inicializa el iterador de la colección. Vacía el iterador actual y apila
   todos los nodos del camino izquierdo desde la raíz, preparando un recorrido
   inorden.
*/
template <typename ident, typename val>
void iniciarIterador(colecInterdep<ident, val> &c) {
  liberar(c.iter);
  typename colecInterdep<ident, val>::Nodo *aux = c.raiz;

  while (aux != nullptr) {
    apilar(c.iter, aux);
    aux = aux->hijoIzq;
  }
}

/* Devuelve true si aún queda algún nodo por visitar con el iterador, false en
   caso contrario.
*/
template <typename ident, typename val>
bool existeSiguiente(const colecInterdep<ident, val> &c) {
  return !esVacia(c.iter);
}
/* Si queda algún nodo por visitar, devuelve en 'sig' su identificador y true.
   Si no quedan elementos o hay error, devuelve false.
*/
template <typename ident, typename val>
bool siguienteIdent(const colecInterdep<ident, val> &c, ident &sig) {
  if (existeSiguiente(c)) {
    typename colecInterdep<ident, val>::Nodo *aux;
    bool error;
    cima(c.iter, aux, error);
    if (!error) {
      sig = aux->id;
      return true;
    }
  }
  return false;
}

/* Si hay un nodo pendiente de visitar, devuelve en 'sig' su valor y true.
   Si el iterador está vacío, devuelve false.
*/
template <typename ident, typename val>
bool siguienteVal(const colecInterdep<ident, val> &c, val &sig) {
  if (existeSiguiente(c)) {
    typename colecInterdep<ident, val>::Nodo *aux;
    bool error;
    cima(c.iter, aux, error);
    if (!error) {
      sig = aux->valor;
      return true;
    }
  }
  return false;
}

/* Si hay un nodo pendiente de visitar, devuelve true si es dependiente y
   false si es independiente. Si no hay nodo, devuelve false.
*/
template <typename ident, typename val>
bool siguienteDependiente(const colecInterdep<ident, val> &c) {
  if (existeSiguiente(c)) {
    typename colecInterdep<ident, val>::Nodo *aux;
    bool error;
    cima(c.iter, aux, error);
    if (!error) {
      if (aux->identSup == nullptr) {
        return false;
      } else {
        return true;
      }
    }
  }
  return false;
}

/* Si el nodo pendiente de visitar es dependiente, devuelve en 'sig' el
   identificador de su supervisor y true. Si es independiente o no hay nodo,
   devuelve false.
*/
template <typename ident, typename val>
bool siguienteSuperior(const colecInterdep<ident, val> &c, ident &sig) {
  if (existeSiguiente(c)) {
    typename colecInterdep<ident, val>::Nodo *aux;
    bool error;
    cima(c.iter, aux, error);
    if (!error) {
      if (aux->identSup == nullptr) {
        return false;
      } else {
        sig = aux->identSup->id;
        return true;
      }
    }
  }
  return false;
}

/* Si hay un nodo pendiente, devuelve en 'num' cuántos dependientes tiene y
   true. Si no quedan elementos, devuelve false.
*/
template <typename ident, typename val>
bool siguienteNumDependientes(const colecInterdep<ident, val> &c, int &num) {
  if (existeSiguiente(c)) {
    typename colecInterdep<ident, val>::Nodo *aux;
    bool error;
    cima(c.iter, aux, error);
    if (!error) {
      num = aux->numDepend;
      return true;
    }
  }
  return false;
}

/* Avanza el iterador al siguiente nodo en recorrido inorden. Devuelve true si
   puede avanzar y false si ya no quedan más elementos.
*/
template <typename ident, typename val>
bool avanza(colecInterdep<ident, val> &c) {
  if (existeSiguiente(c)) {
    typename colecInterdep<ident, val>::Nodo *aux;
    bool error;
    cima(c.iter, aux, error);
    if (!error) {
      desapilar(c.iter);
      aux = aux->hijoDer;

      while (aux != nullptr) {
        apilar(c.iter, aux);
        aux = aux->hijoIzq;
      }
      return true;
    }
  }
  return false;
}

// /* Si existe un elemento con 'id', carga en los parámetros de salida 'valO'
// con su 'valor', 'depen' asignandole true si es dependiente y false en caso
// contrario,
//  modificanco 'idO' solo si es dependiente y 'NumDepO' con su 'NumDepend' y
//  devuelve true. Si 'id' no existe, no modifica ninguno de los parámetros y
//  devuelve false.
//    Esta función existe por eficiencia, para evitar múltiples recorridos O(N).
//    Realiza una única búsqueda optimizada del nodo 'aux' con el 'id' dado.
//    Si no lo encuentra, devuelve 'false'. Si lo encuentra, extrae toda
//    la información ('valO', 'NumDepO') y maneja la lógica de dependencia
//    ('depen' e 'idO') comprobando 'aux->identSup'.
// */
template <typename ident, typename val>
bool obtenerInfo(const colecInterdep<ident, val> &c, const ident &id, val &valO,
                 bool &depen, ident &idO, unsigned int &NumDepO) {
  typename colecInterdep<ident, val>::Nodo *ptrId = nullptr;
  encontrarRec<ident, val>(c.raiz, id, ptrId);
  if (ptrId != nullptr) {
    valO = ptrId->valor;
    if (ptrId->identSup == nullptr) {
      depen = false;
    } else {
      depen = true;
      idO = ptrId->identSup->id;
    }
    NumDepO = ptrId->numDepend;
    return true;
  }
  return false;
}

#endif // _COLECCIONES_INTERDEPENDIENTES_HPP