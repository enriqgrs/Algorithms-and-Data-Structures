//*****************************************************************
// File:    coleccionesInterdependientes.hpp
// Authors: Anastasia Shlyk
//          Enrique José Guaras Lacasta
// Date:    Noviembre 2025
// Coms:    Practica 3 (EDA)
//*****************************************************************

#include <iostream>

#ifndef _COLECCIONESINTERDEPENDIENTES_HPP
#define _COLECCIONESINTERDEPENDIENTES_HPP
using namespace std;

/* INICIO DE LA PARTE PÚBLICA o INTERFAZ  */

/*Los valores del TAD genérico colecInterdep representan colecciones de elementos interdependientes. 
  Donde cada uno de sus elementos se forman conceptualmente como una tupla que contiene un identificador, 
  un valor, un identificador de supervisor y un contador de dependientes: (ident, val, identSup, NumDepend).

  Se distinguen dos tipos de elementos: 'independientes' (ident, val, -, NumDepend), y 'dependientes' (ident, val, identSup, NumDepend), 
  donde 'identSup' es el identificador de otro elemento ya existente en la misma colección.

  Esta colección cuenta con las siguientes restricciones. Primero, no pueden existir dos elementos con el mismo 'ident'. 
  La colección se mantiene siempre ordenada crecientemente según este 'ident'. Ninguno de sus elementos
  puede depender de sí mismo (sus 'id's deben ser distinto de sus 'identSup's).
  Finalmente, el campo 'NumDepend' de un elemento 'A' siempre almacena el número total de elementos en la colección que dependen directamente de 'A'.

  Respecto al coste de esta implementación, las operaciones 'crear', 'tamanyo', 'esVacia' y todas las del iterador tienen un coste constante O(1). 
  Sin embargo, las operaciones que implican búsqueda, inserción o borrado ('existe', 'existeDependiente', 'existeIndependiente', 'anadirIndependiente', 
  'anadirDependiente', 'hacerDependiente', 'hacerIndependiente', 'actualizarVal', 'obtenerVal', 'obtenerSupervisor', 'obtenerNumDependientes', 'borrar' y 'obtenerInfo') 
  tendrán un coste O(N) en el peor caso, siendo N el número de elementos. Este coste se debe a que la implementación se basa en un recorrido secuencial de la lista.
  El coste en memoria de esta implementación es O(N).

  A los parámetros formales genéricos se les exigen ciertos operadores.
  Al parámetro 'ident' le exigimos estar dotado de los operadores de comparación de igualdad (==) y de anterioridad (<), que definen un orden total
  necesario para la ordenación y búsqueda. Al parámetro 'val' se le exige el operador de copia/asignación (=) para poder almacenar y devolver valores.
*/
template<typename ident, typename val> struct colecInterdep;

/* Crea una colección vacía, sin elementos.
*/
template<typename ident, typename val> void crear(colecInterdep<ident, val>& c);

/* Devuelve el número de elementos que hay en la colección c.
*/
template<typename ident, typename val> unsigned int tamanyo(const colecInterdep<ident, val>& c);

/* Devuelve true si y solo si c no contiene ningún elemento, false en caso contrario.
*/
template<typename ident, typename val> bool esVacia(const colecInterdep<ident, val>& c);

/* Devuelve true si existe un elemento en la coleccion c con identificador 'id', false en caso contrario.
*/
template<typename ident, typename val> bool existe(const colecInterdep<ident, val>& c, const ident& id);

/* Devuelve true si existe un elemento en c con identificador 'id' y este es dependiente, false en caso contrario.
*/
template<typename ident, typename val> bool existeDependiente(const colecInterdep<ident, val>& c, const ident& id);

/* Devuelve true si existe un elemento en c con identificador 'id' y este es independiente, false en caso contrario.
*/
template<typename ident, typename val> bool existeIndependiente(const colecInterdep<ident, val>& c, const ident& id);

/* En el caso de que no exista un elemento con 'id', añade un nuevo elemento independiente (id, v, -, 0) a la colección 'c' manteniéndola ordenada devolviendo true. 
  Si ya existe 'id', no modifica 'c' y devuelve false.
*/
template<typename ident, typename val> bool anadirIndependiente(colecInterdep<ident, val>& c, const ident& id, const val& v);

/* En el caso de que no exista 'id', sí exista 'super', y 'id' != 'super', añade un nuevo elemento dependiente (id, v, super, 0) a la colección 'c'
 manteniéndola ordenada, incrementa en 1 el 'NumDepend' del supervisor 'super' y devuelve true. Si 'id' ya existe, 'super' no existe, o 'id' == 'super',
 no modifica 'c' y devuelve false.
*/
template<typename ident, typename val> bool anadirDependiente(colecInterdep<ident, val>& c, const ident& id, const val& v, const ident& super);

/* En el caso de que existan 'id' y 'super', y 'id' != 'super', modifica 'id' para que dependa de 'super'. Si 'id' ya era dependiente, decrementa en 1 la
 contabilidad de su antiguo supervisor. E incrementa en 1 el 'NumDepend' de 'super'. Devuelve true si la operación se realiza. Si 'id' o 'super' no existen o
 son iguales, devuelve false.
*/
template<typename ident, typename val> bool hacerDependiente(colecInterdep<ident, val>& c, const ident& id, const ident& super);

/* En el caso de que exista 'id' y sea dependiente, lo convierte en independiente. Decrementa en 1 el 'NumDepend' de su antiguo supervisor.
 Devuelve true si la operación se realiza. Si 'id' no existe o ya era independiente, devuelve false.
*/
template<typename ident, typename val> bool hacerIndependiente(colecInterdep<ident, val>& c, const ident& id);

/* En el caso de que exista un elemento con 'id', actualiza su campo 'valor' con el 'nuevo' valor y devuelve true. Si 'id' no existe, devuelve false.
*/
template<typename ident, typename val> bool actualizarVal(colecInterdep<ident, val>& c, const ident& id, const val& nuevo);

/* En el caso de que exista un elemento con 'id', carga en 'valO' su valor y devuelve true. Si 'id' no existe, no modifica 'valO' y devuelve false.
*/
template<typename ident, typename val> bool obtenerVal(const colecInterdep<ident, val>& c, const ident& id, val& valO);

/* En el caso de que exista 'id' y sea dependiente, carga en 'idO' el identificador de su supervisor y devuelve true. Si 'id' no existe o es
 independiente, no modifica 'idO' y devuelve false.
*/
template<typename ident, typename val> bool obtenerSupervisor(const colecInterdep<ident, val>& c, const ident& id, ident& idO);

/* En el caso de que exista un elemento con 'id', carga en 'NumDepO' su número de dependientes directos y devuelve true. Si 'id' no existe, no modifica
 'NumDepO' y devuelve false.
*/
template<typename ident, typename val> bool obtenerNumDependientes(const colecInterdep<ident, val>& c, const ident& id, unsigned int& NumDepO);

/* En el caso de que exista 'id' y no tenga dependientes ('NumDepend' sea 0), lo elimina de la colección respetando el orden. Si 'id' era dependiente, actualiza la contabilidad
 de su supervisor quitando 1 en 'NumDepend'. Devuelviendo true si se borra. Si 'id' no existe o tiene dependientes, no modifica 'c' y devuelve false.
*/
template<typename ident, typename val> bool borrar(colecInterdep<ident, val>& c, const ident& id);


// --- OPERACIONES DEL ITERADOR ---

/* Prepara el iterador para que el siguiente elemento a visitar sea el primero de la colección (el de 'ident' menor).
 Devuelve verdadero si hay elementos para iterar, falso si la colección está vacía.
*/
template<typename ident, typename val> bool iniciarIterador( colecInterdep<ident, val>& c);

/* Devuelve true si queda algún elemento por visitar, false en caso contrario.
*/
template<typename ident, typename val> bool existeSiguiente(const colecInterdep<ident, val>& c);

/* Si existe un elemento pendiente de visitar, carga en 'sig' su 'ident' y devuelve true. 
  Si no quedan elementos por visitar, devuelve false.
*/
template<typename ident, typename val> bool siguienteIdent(const colecInterdep<ident, val>& c, ident &sig);

/* Si existe un elemento pendiente de visitar, carga en 'sig' su 'valor' y devuelve true. 
  Si no quedan elementos por visitar, devuelve false.
*/
template<typename ident, typename val> bool siguienteVal(const colecInterdep<ident, val>& c, val& sig);

/* Si existe un elemento pendiente de visitar, devuelve true si este es dependiente, o false si es independiente. 
  Si no quedan elementos, devuelve false.
*/
template<typename ident, typename val> bool siguienteDependiente(const colecInterdep<ident, val>& c);

/* Si existe un elemento pendiente de visitar y es dependiente, carga en 'sig' el 'ident' de su supervisor y devuelve true. 
  Si no quedan elementos o el actual es independiente, devuelve false.
*/
template<typename ident, typename val> bool siguienteSuperior(const colecInterdep<ident, val>& c, ident &sig);

/* Si existe un elemento pendiente de visitar, carga en 'num' su 'NumDepend'y devuelve true. 
  Si no quedan elementos por visitar, devuelve false.
*/
template<typename ident, typename val> bool siguienteNumDependientes(const colecInterdep<ident, val>& c, unsigned int &num);

/* Si existe un elemento pendiente de visitar, avanza el iterador al siguiente elemento y devuelve true. 
Si no quedan elementos (el iterador está al final), no avanza y devuelve false.
*/
template<typename ident, typename val> bool avanza(colecInterdep<ident, val>& c);

/* Si existe un elemento con 'id', carga en los parámetros de salida 'valO' con su 'valor', 'depen' asignandole true si es dependiente y false en caso contrario,
 modificanco 'idO' solo si es dependiente y 'NumDepO' con su 'NumDepend' y devuelve true.
 Si 'id' no existe, no modifica ninguno de los parámetros y devuelve false.
*/
template<typename ident, typename val> bool obtenerInfo(const colecInterdep<ident, val>& c, const ident& id, val& valO, bool& depen, ident& idO, unsigned int& NumDepO);

// FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)



// DECLARACION DEL TAD GENERICO coleccionesInterdependientes

template<typename ident, typename val>
struct colecInterdep{
  friend void crear<ident, val>(colecInterdep<ident, val>& c);
  friend bool esVacia<ident, val>(const colecInterdep<ident, val>& c);
  friend bool existe<ident, val>(const colecInterdep<ident, val>& c, const ident& id);
  friend unsigned int tamanyo <ident, val> (const colecInterdep<ident, val>& c);
  friend bool existeDependiente <ident, val> (const colecInterdep<ident, val>& c, const ident& id);
  friend bool existeIndependiente <ident, val> (const colecInterdep<ident, val>& c, const ident& id);
  friend bool anadirIndependiente <ident, val> (colecInterdep<ident, val>& c, const ident& id, const val& v);
  friend bool anadirDependiente <ident, val> (colecInterdep<ident, val>& c, const ident& id, const val& v, const ident& super);
  friend bool hacerDependiente <ident, val> (colecInterdep<ident, val>& c, const ident& id, const ident& super);
  friend bool hacerIndependiente <ident, val> (colecInterdep<ident, val>& c, const ident& id);
  friend bool actualizarVal <ident, val> (colecInterdep<ident, val>& c, const ident& id, const val& nuevo);
  friend bool obtenerVal <ident, val> (const colecInterdep<ident, val>& c, const ident& id, val& valO);
  friend bool obtenerSupervisor <ident, val> (const colecInterdep<ident, val>& c, const ident& id, ident& idO);
  friend bool obtenerNumDependientes <ident, val> (const colecInterdep<ident, val>& c, const ident& id, unsigned int& NumDepO);
  friend bool borrar <ident, val> (colecInterdep<ident, val>& c, const ident& id);
  friend bool iniciarIterador <ident, val> ( colecInterdep<ident, val>& c);
  friend bool existeSiguiente <ident, val> (const colecInterdep<ident, val>& c);
  friend bool siguienteIdent <ident, val> (const colecInterdep<ident, val>& c, ident &sig);
  friend bool siguienteVal <ident, val> (const colecInterdep<ident, val>& c, val& sig);
  friend bool siguienteDependiente <ident, val> (const colecInterdep<ident, val>& c);
  friend bool siguienteSuperior <ident, val> (const colecInterdep<ident, val>& c, ident &sig);
  friend bool siguienteNumDependientes <ident, val> (const colecInterdep<ident, val>& c, unsigned int &num);
  friend bool avanza <ident, val> (colecInterdep<ident, val>& c);
  friend bool obtenerInfo <ident, val> (const colecInterdep<ident, val>& c, const ident& id, val& valO, bool& depen, ident& idO, unsigned int& NumDepO);

  private:
    /*
    La implementación de este TAD se basa en una lista enlazada simple, que se mantiene ordenada crecientemente por el campo 'id' de los nodos. 
    La estructura 'colecInterdep' almacena un puntero 'primElmt' al primer nodo de la lista, siendo 'nullptr' si la colección está vacía.
    
    Se incluye un contador 'numElem' para el total de elementos. Esta decisión de diseño es crucial para que las operaciones 'tamanyo' y 'esVacia' tengan
    un coste computacional O(1). Se usa un puntero 'iter' para gestionar el estado del iterador interno, apuntando al siguiente nodo a visitar o a 'nullptr' si la iteración ha concluido.

    El 'struct Nodo' define la estructura interna de cada elemento. Contiene el 'id' (que actúa como clave de ordenación), el 'valor', un puntero 'identSup' que apunta directamente al nodo supervisor 
    (o es 'nullptr' si es independiente) para recudir el coste computacional de borrar o hacerIndependiente al no tener que volver a buscar al padre para decrementar su numDependientes,
    el contador 'numDepend', y un puntero 'siguiente' al próximo nodo de la lista.
    */
    struct Nodo {
        ident id;
        val valor;
        Nodo* identSup = nullptr;
        unsigned int numDepend = 0;
        Nodo* siguiente;
      
    };
    Nodo* primElmt; // Puntero al primer elemento de la lista
    unsigned int numElem; // Número total de elementos
    Nodo* iter; // Puntero de estado del iterador
};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO coleccionesInterdependientes

/* Crea una colección vacía, sin elementos.
   Inicializa la colección estableciendo el puntero 'primElmt' a 'nullptr' y lo mismo con el iterador 'iter' a 'nullptr'. 
   El contador de elementos 'numElem' se inicializa a 0 para reflejar que la colección está vacía.
*/
template<typename ident, typename val> void crear(colecInterdep<ident, val>& c){
    c.primElmt = nullptr;
    c.numElem=0;
    c.iter = nullptr;
}

/* Devuelve el número de elementos que hay en la colección c.
   La operación devuelve directamente el valor del contador 'numElem'.
   Gracias a mantener este contador actualizado en las operaciones de inserción y borrado, esta consulta tiene un coste O(1).
*/
template<typename ident, typename val> unsigned int tamanyo(const colecInterdep<ident, val>& c){
    return c.numElem;
}

/* Devuelve true si y solo si c no contiene ningún elemento, false en caso contrario.
   La eficiencia de esta operación es O(1) dado que la estructura mantiene un contador 'numElem' con el total de elementos.
   Por lo tanto, la función simplemente comprueba si dicho contador es igual a 0.
*/
template<typename ident, typename val> bool esVacia(const colecInterdep<ident, val>& c){
    return (c.numElem==0);
}

/* Devuelve true si existe un elemento en la coleccion c con identificador 'id', false en caso contrario.
   Se realiza un recorrido secuencial de la lista enlazada desde 'primElmt' optimizada gracias a que la lista está ordenada: el recorrido (puntero 'aux') 
   avanza solo mientras no llege al final ('aux == nullptr') o si se encuentra un 'id' mayor o igual. Devolviendo true solo si 'aux' no es
   nulo y 'aux->id == id'.
*/
template<typename ident, typename val> bool existe(const colecInterdep<ident, val>& c, const ident& id){
  typename colecInterdep<ident, val>::Nodo* aux = c.primElmt;
  //Busqueda iterativa ordenada
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
  //devolveremos true solo si es el dato que buscamos
    return (aux != nullptr && aux->id == id); //Clave verificar previamente que no sea un nullptr antes de acceder (andthen)
}

/* Devuelve true si existe un elemento en c con identificador 'id' y este es dependiente (tiene un supervisor), false en caso contrario.
   Realizamos la misma lógica de búsqueda optimizada de la operación 'existe()'. Tras encontrar el nodo (si 'aux != nullptr && aux->id == id'), se
   añade una comprobación adicional para verificar que el puntero al supervisor, 'aux->identSup', sea distinto de 'nullptr'.
*/
template<typename ident, typename val> bool existeDependiente(const colecInterdep<ident, val>& c, const ident& id){
  typename colecInterdep<ident, val>::Nodo* aux = c.primElmt;
  //Busqueda iterativa ordenada
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
  //devolveremos true solo si es el dato que buscamos y depende de otro
    return (aux != nullptr && aux->id == id && aux->identSup != nullptr);
}

/* Devuelve true si existe un elemento en c con identificador 'id' y este es independiente (no tiene supervisor), false en caso contrario.
   Similar a 'existeDependiente()', realiza la búsqueda optimizada del elemento. Si se encuentra, se comprueba que su puntero supervisor
   'aux->identSup' sea igual a 'nullptr', lo que define a un nodo como independiente.
*/
template<typename ident, typename val> bool existeIndependiente(const colecInterdep<ident, val>& c, const ident& id){
  typename colecInterdep<ident, val>::Nodo* aux = c.primElmt;
  //Busqueda iterativa ordenada
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
  //devolveremos true solo si es el dato que buscamos y no depende de otro
    return (aux != nullptr && aux->id == id && aux->identSup == nullptr);
}

/* En el caso de que no exista un elemento con 'id', añade un nuevo elemento independiente (id, v, -, 0) a la colección 'c' manteniéndola ordenada devolviendo true. 
  Si ya existe 'id', no modifica 'c' y devuelve false.
   Plantearemos 3 casos diferentes.
   - Si la lista está vacía, el nuevo nodo se convierte en 'primElmt'.
   - Si el nuevo 'id' es menor que 'c.primElmt->id', el nuevo nodo se inserta al principio de la lista.
      Deberemos comprovar este primer valor puesto que la busqueda a posteriori no valora este caso, al usar un solo puntero el cual comparara con el nodo siguiente al que nos encontramos para 
      hacer una inserción directa (Previo->NodoNuevo->Siguiente) para apuntar al nuevo dato directamente.]
   - En el caso general, se busca el nodo *anterior* ('aux') al punto de inserción. La búsqueda se detiene cuando 'aux->siguiente' es 'nullptr' o 'aux->siguiente->id' ya no es menor que 'id'.
   En los casos 2 y 3, se comprueba si el 'id' ya existe, en cuyo caso se devuelve 'false', haciendo asi que no haya que recorrer toda la lista multiples veces. Si se inserta, ademas incrementa 'c.numElem'.
*/
template<typename ident, typename val> bool anadirIndependiente(colecInterdep<ident, val>& c, const ident& id, const val& v){
  //Lista vacia. Inserción directa.
    if(esVacia(c)){
      typename colecInterdep<ident, val>::Nodo* auxN = new typename colecInterdep<ident, val>::Nodo;
        auxN->id=id;
        auxN->valor=v;
        auxN->identSup=nullptr;
        auxN->numDepend = 0;
        auxN->siguiente=nullptr;
        c.primElmt = auxN;
        c.numElem=1;
      return true;
      }
  //Comprovamos que no sea el primer dato al no estudiarlo en la busqueda futura
    if (c.primElmt->id == id) {
      return false; //primero repetido
  //Caso de que realmente fuera primero, tampoco se valora en la busqueda futura.
    }else if (id < c.primElmt->id) {
      typename colecInterdep<ident, val>::Nodo* auxN = new typename colecInterdep<ident, val>::Nodo;
      auxN->siguiente=c.primElmt;
      c.primElmt=auxN;
      auxN->id=id;
      auxN->valor=v;
      auxN->identSup=nullptr;
      auxN->numDepend=0;
      c.numElem++;
      return true;
    }
  //Empieza la el caso general
    typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
    //Busqueda desde el nodo anterior para reducir el numero de punteros
      while(aux->siguiente != nullptr && aux->siguiente->id < id){
        aux = aux->siguiente;
      } 
    //Si se para la busqueda comprovamos que hayamos encontrado lo que buscabamos
    if(aux->siguiente != nullptr && aux->siguiente->id==id){
      return false;
    }
    //Generación del nodo
    typename colecInterdep<ident, val>::Nodo* auxN = new typename colecInterdep<ident, val>::Nodo;
      auxN->siguiente=aux->siguiente;
      aux->siguiente=auxN;
      auxN->id=id;
      auxN->valor=v;
      auxN->identSup=nullptr;
      auxN->numDepend=0;
      c.numElem++;
    return true;
}

/* En el caso de que no exista 'id', sí exista 'super', y 'id' != 'super', añade un nuevo elemento dependiente (id, v, super, 0) a la colección 'c'
 manteniéndola ordenada, incrementa en 1 el 'NumDepend' del supervisor 'super' y devuelve true. Si 'id' ya existe, 'super' no existe, o 'id' == 'super',
 no modifica 'c' y devuelve false.
   Se aborta si la lista está vacía (el supervisor no puede existir) o si 'id == super'.
   Se maneja el caso especial de la busqueda de la inserción (como en anadirDependiente, un solo puntero que apunte al siguiente para una inserción directa genera una preevaluación del primer elemento). 
   Para el caso general, se deben encontrar: el supervisor ('auxP', busqueda directa con el nodo) y la posición de inserción (el nodo anterior, 'auxH', busqueda con siguiente).
   Ademas para optimizar el recorrido, se aprovecha el orden. Realizando una busqueda con punteros en 2 turnos con relevo. 
      Si 'id < super', se busca primero 'auxH' dejando un puntero a este y luego buscamos a 'auxP' con otro puntero a partir de esa posición. Y biceversa.
   Si todo es correcto, se crea el nodo, se enlaza en la lista (modificando c), se asigna 'auxN->identSup = auxP', y se incrementan 'auxP->numDepend' y 'c.numElem'.
*/
template<typename ident, typename val> bool anadirDependiente(colecInterdep<ident, val>& c, const ident& id, const val& v, const ident& super){
  //Si esta vacia es imposible generar un dato dependiente y tampoco puede depender de si mismo
    if(esVacia(c)||(id==super)){
      return false; 
    }
  //Analisis del primer elemento debido al tipo de busqueda con un unico puntero
    if (c.primElmt->id == id) {
      return false;
    }
    if (id < c.primElmt->id) { // Caso especial: Inserción al principio
        typename colecInterdep<ident, val> ::Nodo* auxP = c.primElmt;
        //Busqueda directa presente al buscar su existencia no se hueco
        while(auxP!=nullptr && auxP->id < super){
          auxP = auxP->siguiente;
        }
        if(auxP==nullptr || auxP->id!=super){return false;}
        typename colecInterdep<ident, val>::Nodo* auxH = new typename colecInterdep<ident, val>::Nodo;
        auxH->id=id;
        auxH->valor=v;
        auxH->identSup=auxP;
        auxH->numDepend = 0;
        auxH->siguiente=c.primElmt;
        c.primElmt = auxH;
        c.numElem++;
        auxP->numDepend++;
        return true;
    }
  //Caso general, subidivididos por ordenes de ids
  //Pregeneramos los punteros para legibilidad de codigo
    typename colecInterdep<ident, val> ::Nodo* auxH;
    typename colecInterdep<ident, val> ::Nodo* auxP;
    //Primero buscamos el hueco y despues de a quien va a depender
      if(id<super){
        auxH = c.primElmt;
        //Busqueda desde el nodo anterior para reducir el numero de punteros
          while(auxH->siguiente != nullptr && auxH->siguiente->id < id){
              auxH = auxH->siguiente;
          }
          if(auxH->siguiente != nullptr && auxH->siguiente->id==id){return false;}
        //Paso de relevo
          auxP = auxH->siguiente;//tiene que ser extrictamente mayor al del hueco por ser id<super
        //Busqueda directa presente al buscar su existencia no se hueco
          while(auxP!= nullptr && auxP->id < super){
              auxP = auxP->siguiente;
          }
          if(auxP==nullptr || auxP->id!=super){return false;}
      }else{ 
        auxP=c.primElmt;
        //Busqueda directa presente al buscar su existencia no se hueco
          while(auxP!= nullptr && auxP->id < super){
              auxP = auxP->siguiente;
          }
          if(auxP==nullptr || auxP->id!=super){return false;}
        //Paso de relevo
          auxH = auxP;
        //Busqueda desde el nodo anterior para reducir el numero de punteros
          while(auxH->siguiente != nullptr && auxH->siguiente->id < id){
              auxH = auxH->siguiente;
          }
        if(auxH->siguiente != nullptr && auxH->siguiente->id==id){return false;}
      }
      //Si hemos llegado aqui para el caso general es seguro que hemos encontrado y se cumple todo lo necesario.
      typename colecInterdep<ident, val>::Nodo* auxN = new typename colecInterdep<ident, val>::Nodo;
      auxN->siguiente=auxH->siguiente;
      auxH->siguiente=auxN;
      auxN->id=id;
      auxN->valor=v;
      auxN->identSup=auxP;
      auxP->numDepend++;
      auxN->numDepend=0;
      c.numElem++;
      return true;
    
}

/* En el caso de que existan 'id' y 'super', y 'id' != 'super', modifica 'id' para que dependa de 'super'. Si 'id' ya era dependiente, decrementa en 1 la
 contabilidad de su antiguo supervisor. E incrementa en 1 el 'NumDepend' de 'super'. Devuelve true si la operación se realiza. Si 'id' o 'super' no existen o
 son iguales, devuelve false.
   Abortamos si 'id == super'. Realiza la misma búsqueda optimizada que en 'anadirDependiente' para localizar los nodos 'id' ('aux') y 'super' ('auxP'), por relevo y en función de su orden. 
   Ambas comprobadas desde el mismo nodo, ya no buscamos huecos. Y si no encontramos alguno de estos salimos directamente.
   Si alguno de los datos que necesitamos no los encontramos, se devuelve 'false'. Si se encuentran ambos, se valora si el nodo 'aux' ya tenía un supervisor ('aux->identSup != nullptr'). 
   De ser así, se decrementa el contador 'numDepend'de ese antiguo supervisor. Finalmente, se asigna 'aux->identSup = auxP' y se incrementa 'auxP->numDepend' del nuevo dependiente.
*/
template<typename ident, typename val> bool hacerDependiente(colecInterdep<ident, val>& c, const ident& id, const ident& super){
  //Comprovamos el caso critico 
  if(esVacia(c)||(id==super)){return false;}
  //Parecido a la funcion anterior, busqueda doble de 2 entidades subdividos con el paso de relevo.
    typename colecInterdep<ident, val> ::Nodo* aux;
    typename colecInterdep<ident, val> ::Nodo* auxP;
    //Orden 1
      if(id<super){
        aux = c.primElmt;
        //Busqueda del primer termino
          while(aux != nullptr && aux->id < id){
            aux = aux->siguiente;
          }
          if(aux== nullptr || aux->id!=id){return false;}
        //Paso de relevo
          auxP=aux->siguiente;
        //Busqueda del segundo termino
          while(auxP!= nullptr && auxP->id < super){
            auxP = auxP->siguiente;
          }
          if(auxP==nullptr||auxP->id!=super){return false;}
    //Orden 2
      }else{
        auxP = c.primElmt;
        //Busqueda del primer termino
          while(auxP != nullptr && auxP->id < super){
            auxP = auxP->siguiente;
          }
          if(auxP== nullptr || auxP->id!=super){return false;}
        //Paso de relevo
        aux=auxP->siguiente;
        //Busqueda del segundo termino
          while(aux!= nullptr && aux->id < id){
            aux = aux->siguiente;
          }
          if(aux==nullptr||aux->id!=id){return false;}
      }
    //Datos encontrados comprovación y modificación
      if(aux->identSup != nullptr){
        aux->identSup->numDepend--;
      }
      aux->identSup = auxP;
      auxP->numDepend++;
      return true;
}

/*En el caso de que exista 'id' y sea dependiente, lo convierte en independiente. Decrementa en 1 el 'NumDepend' de su antiguo supervisor.
 Devuelve true si la operación se realiza. Si 'id' no existe o ya era independiente, devuelve false.
   Buscamos el nodo con 'id' ('aux') usando el recorrido optimizado. Si se encuentra y se confirma que es dependiente ('aux->identSup != nullptr'),
   se accede a su supervisor ('aux->identSup') y se decrementa 'numDepend'.
   Para despues establecer 'aux->identSup = nullptr' para marcarlo como independiente. Si no se encuentra o ya era independiente, devuelve 'false'.
*/
template<typename ident, typename val> bool hacerIndependiente(colecInterdep<ident, val>& c, const ident& id){
  typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
  //Realizamos la busqueda
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
  //En caso de si ser dependiente podemos realizar la modificacion
  if(aux != nullptr && aux-> id == id && aux->identSup != nullptr){
    aux->identSup->numDepend--;
    aux->identSup = nullptr;
    return true;
  }
  return false;
}

/* En el caso de que exista un elemento con 'id', actualiza su campo 'valor' con el 'nuevo' valor y devuelve true. Si 'id' no existe, devuelve false.
   Busca el nodo con 'id' ('aux'). Si lo encuentra, se sobrescribe su campo 'valor' con el 'nuevo' valor y se devuelve 'true'.
   Si el bucle termina sin encontrarlo, devuelve 'false'.
*/
template<typename ident, typename val> bool actualizarVal(colecInterdep<ident, val>& c, const ident& id, const val& nuevo){
  typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
  //Realizamos la busqueda
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
  //Verificar si hemos encontrado el valor
    if(aux == nullptr || id!=aux->id){return false;}
    aux->valor = nuevo;
    return true;
}

/*En el caso de que exista un elemento con 'id', carga en 'valO' su valor y devuelve true. Si 'id' no existe, no modifica 'valO' y devuelve false.
   Se busca el nodo con 'id' ('aux'). Si lo encuentra, se le asigna el valor 'valO = aux->valor' y se devuelve 'true'. En caso contrario, 'false'.
*/
template<typename ident, typename val> bool obtenerVal(const colecInterdep<ident, val>& c, const ident& id, val& valO){
  typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
  //Realizamos la busqueda
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
  //Verificar si hemos encontrado el valor
    if(aux == nullptr || id!=aux->id){return false;}
    valO=aux->valor;
    return true;
}


/* En el caso de que exista 'id' y sea dependiente, carga en 'idO' el identificador de su supervisor y devuelve true. Si 'id' no existe o es
 independiente, no modifica 'idO' y devuelve false.
   Se busca el nodo con 'id' ('aux'). Si lo encuentra y se confirma que es dependiente, se asigna el identificador
   del supervisor 'idO = aux->identSup->id' y se devuelve 'true'. Si no se encuentra o es independiente, devuelve 'false'.
*/
template<typename ident, typename val> bool obtenerSupervisor(const colecInterdep<ident, val>& c, const ident& id, ident& idO){
  typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
  //Realizamos la busqueda
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
  //Verificar si hemos encontrado el valor
    if(aux == nullptr || id!=aux->id || aux->identSup == nullptr){return false;}
    idO=aux->identSup->id;
    return true;
}

/* En el caso de que exista un elemento con 'id', carga en 'NumDepO' su número de dependientes directos y devuelve true. Si 'id' no existe, no modifica
 'NumDepO' y devuelve false.
   Se busca el nodo con 'id' ('aux'). Si se encuentra, se asigna el valor 'NumDepO = aux->numDepend' y se devuelve 'true'. En caso contrario, devolveremos 'false'.
*/
template<typename ident, typename val> bool obtenerNumDependientes(const colecInterdep<ident, val>& c, const ident& id, unsigned int& NumDepO){
  typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
  while(aux != nullptr && aux->id < id){
    aux = aux->siguiente;
  }
  if(aux == nullptr || id!=aux->id){return false;}
  NumDepO=aux->numDepend;
  return true;
}

/* En el caso de que exista 'id' y no tenga dependientes ('NumDepend' sea 0), lo elimina de la colección respetando el orden. Si 'id' era dependiente, actualiza la contabilidad
 de su supervisor quitando 1 en 'NumDepend'. Devuelviendo true si se borra. Si 'id' no existe o tiene dependientes, no modifica 'c' y devuelve false.
    Como se nos ha planteado en situaciones anteriores, realizaremos un borrado desde un nodo anterior (apuntando al dato), para apuntar desde el nodo anterior al siguiente respecto al que vamos a borrar,
    por lo cual prevaloraremos el primer termino y con un puntero auxiliar liberar su memoria para no generar basura.
      - Borrar el primer elemento ('c.primElmt->id == id'). Se comprueba que 'numDepend' sea 0. Si lo es, se actualiza el 'primElmt' al siguiente.
      - Borrar un elemento intermedio o final. Se busca el nodo *anterior* ('aux') al que se desea borrar. Se comprueba que 'aux->siguiente' sea el nodo correcto y que su 'numDepend' sea 0. Si es así, se puentea ('aux->siguiente = controlador->siguiente').
   En ambos casos, si el nodo a borrar era dependiente ('identSup != nullptr'), se decrementa 'numDepend' de su supervisor. Finalmente, se libera la memoria del nodo y se decrementa 'c.numElem'.
*/
template<typename ident, typename val> bool borrar(colecInterdep<ident, val>& c, const ident& id){
  //Si es vacia no hay dato que podamos borrar
    if(esVacia(c)){return false;}
  //Precomprovación 
    if (c.primElmt->id == id) {
      //Si tiene dependientes no podemos borrarlo 
        if (c.primElmt->numDepend != 0) {
          return false;
        }
      //Si este dependia de alguien decrementaremos su valor
        if (c.primElmt->identSup != nullptr) {
          c.primElmt->identSup->numDepend--;
        }
      //Y realizaremos su borrado
      typename colecInterdep<ident, val> ::Nodo* controlador = c.primElmt;
      c.primElmt = c.primElmt->siguiente;
      delete controlador;
      c.numElem--;
      return true;
    }
  //Caso general, busqueda desde atras, no quedandonos otra de generar el puntero
    typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
    while(aux->siguiente != nullptr && aux->siguiente->id < id){
      aux = aux->siguiente;
    }
  //Verificamos que el dato encontrado es el que queremos
    if(aux->siguiente == nullptr || aux->siguiente->id!=id || aux->siguiente->numDepend!=0){return false;}
  //Realizamos el borrado
    typename colecInterdep<ident, val> ::Nodo* controlador = aux->siguiente;
    if (controlador->identSup != nullptr) {
          controlador->identSup->numDepend--;
    }
    aux->siguiente=controlador->siguiente;
    delete(controlador);
    c.numElem--;
    return true;
}


// --- IMPLEMENTACION OPERACIONES ITERADOR ---

/* Prepara el iterador para que el siguiente elemento a visitar sea el primero de la colección (el de 'ident' menor).
 Devuelve verdadero si hay elementos para iterar, falso si la colección está vacía.
   Asigna el puntero 'c.iter' para que apunte al primer nodo 'c.primElmt'. Devuelve 'true' si este puntero no es 'nullptr', indicando que hay al
   menos un elemento para visitar.
*/
template<typename ident, typename val> bool iniciarIterador( colecInterdep<ident, val>& c){
  //apuntamos al primer elemento y devolveremos si hay algo a lo que apuntar  
    c.iter = c.primElmt;
    return (c.iter != nullptr);
}

/* Devuelve true si queda algún elemento por visitar, false en caso contrario.
   Comprueba si el puntero 'c.iter' es distinto de 'nullptr'. Si no lo es, significa que se ha alcanzado el final de la lista o que esta estaba vacía.
*/
template<typename ident, typename val> bool existeSiguiente(const colecInterdep<ident, val>& c){
  //Comprovación de si despues tendremos un dato
    return (c.iter != nullptr);
}

/* Si existe un elemento pendiente de visitar, carga en 'sig' su 'ident' y devuelve true. Si no quedan elementos por visitar, devuelve false.
   Comprueba si 'c.iter' es válido (no 'nullptr'). Si lo es, accede al campo 'id' del nodo actual y lo asigna a 'sig'.
*/
template<typename ident, typename val> bool siguienteIdent(const colecInterdep<ident, val>& c, ident &sig){
  //Si hay un dato cogeremos su valor
    if(c.iter !=nullptr){
      sig = c.iter -> id;
      return true;
    }
    return false;
}

/* Si existe un elemento pendiente de visitar, carga en 'sig' su 'valor' y devuelve true. Si no quedan elementos por visitar, devuelve false.
   Comprueba si 'c.iter' es válido. Si lo es, accede al campo 'valor' del nodo actual y lo asigna a 'sig'.
*/
template<typename ident, typename val> bool siguienteVal(const colecInterdep<ident, val>& c, val& sig){
  //Si hay un dato cogeremos su valor
    if(c.iter !=nullptr){
      sig = c.iter -> valor;
      return true;
    }
    return false;
}

/* Si existe un elemento pendiente de visitar, devuelve true si este es dependiente, o false si es independiente. Si no quedan elementos, devuelve false.
   Comprueba si 'c.iter' es válido. Si lo es, devuelve el resultado de la comprobación 'c.iter->identSup != nullptr'.
*/
template<typename ident, typename val> bool siguienteDependiente(const colecInterdep<ident, val>& c){
  //Comprovamos si hay siguiente y depende de alguien
    if (c.iter != nullptr) {
      return (c.iter->identSup != nullptr);
    }
    return false;
}

/* Si existe un elemento pendiente de visitar y es dependiente, carga en 'sig' el 'ident' de su supervisor y devuelve true. 
  Si no quedan elementos o el actual es independiente, devuelve false.
   Realiza una doble comprobación: 'c.iter != nullptr' (para asegurar que hay un elemento) y 'c.iter->identSup != nullptr' (para asegurar que es dependiente). 
   Si ambas son ciertas, accede al 'id' del nodo supervisor.
*/
template<typename ident, typename val> bool siguienteSuperior(const colecInterdep<ident, val>& c, ident &sig){
  //Comprovaremos si depende de alguien y pasaremos su valor
    if(c.iter !=nullptr && c.iter->identSup != nullptr){
      sig = c.iter->identSup->id;
      return true;
    }return false;
}

/* Si existe un elemento pendiente de visitar, carga en 'num' su 'NumDepend' y devuelve true. Si no quedan elementos por visitar, devuelve false.
   Comprueba si 'c.iter' es válido. Si lo es, accede al campo 'numDepend' del nodo actual y lo asigna a 'num'.
*/
template<typename ident, typename val> bool siguienteNumDependientes(const colecInterdep<ident, val>& c, unsigned int &num){
  //Comprovaremos si hay siguiente elemento, asignandole su numDependientes
    if(c.iter !=nullptr){
      num= c.iter->numDepend;
      return true;
    }return false;
}

/* Si existe un elemento pendiente de visitar, avanza el iterador al siguiente elemento y devuelve true. 
Si no quedan elementos (el iterador está al final), no avanza y devuelve false.
   Comprueba si 'c.iter' es válido. Si lo es, actualiza 'c.iter' para que apunte a 'c.iter->siguiente' (que será 'nullptr' si era el último nodo)
   y devuelve 'true' indicando que el avance fue posible.
*/
template<typename ident, typename val> bool avanza(colecInterdep<ident, val>& c){
  //avanzamos siempre que se pueda
    if(c.iter !=nullptr){
      c.iter = c.iter->siguiente;
      return true;
    }return false;
}

/* Si existe un elemento con 'id', carga en los parámetros de salida 'valO' con su 'valor', 'depen' asignandole true si es dependiente y false en caso contrario,
 modificanco 'idO' solo si es dependiente y 'NumDepO' con su 'NumDepend' y devuelve true.
 Si 'id' no existe, no modifica ninguno de los parámetros y devuelve false.
   Esta función existe por eficiencia, para evitar múltiples recorridos O(N).
   Realiza una única búsqueda optimizada del nodo 'aux' con el 'id' dado.
   Si no lo encuentra, devuelve 'false'. Si lo encuentra, extrae toda
   la información ('valO', 'NumDepO') y maneja la lógica de dependencia
   ('depen' e 'idO') comprobando 'aux->identSup'.
*/
template<typename ident, typename val> bool obtenerInfo(const colecInterdep<ident, val>& c, const ident& id, val& valO, bool& depen, ident& idO, unsigned int& NumDepO){
  typename colecInterdep<ident, val> ::Nodo* aux = c.primElmt;
  //Buscaremos el dato y comprovaremos que es ese
    while(aux != nullptr && aux->id < id){
      aux = aux->siguiente;
    }
    if(aux == nullptr || id!=aux->id){return false;}
  //asignaremos sus valores
    valO=aux->valor;
    NumDepO=aux->numDepend;
  //Si es dependiente marcaremos la flag a true para saber que pueden acceder y asignaremos su id para su lectura.
    if(aux->identSup!=nullptr){
      idO=aux->identSup->id;
      depen=true;
    }
    else{
      depen=false;
    }
  //Mientras encontremos el dato hay true
  return true;
}

#endif // _COLECCIONESINTERDEPENDIENTES_HPP