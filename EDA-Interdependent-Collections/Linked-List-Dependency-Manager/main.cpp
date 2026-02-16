//*****************************************************************
// File:    main.cpp
// Authors: Anastasia Shlyk
//          Enrique José Guaras Lacasta
// Date:    Noviembre 2025
// Coms:    Practica 3 (EDA)
//*****************************************************************

#include "coleccionesInterdependientes.hpp"
#include "evento.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const string ID_VACIO = "-.-.-.-.-";

// Convierte un evento dependiente en independiente.
// Si se puede independizar, escribe "INDEPENDIZADO" en el fichero de salida.
// Si ya era independiente, indica "YA ERA INDepend.".
// Si no se puede, indica "NO INDEPENDIZADO".
void hacerIndependienteEvento(ifstream& f, ofstream& g, colecInterdep<string, Evento>& c) {
    string id;
    getline(f, id);
    if (hacerIndependiente(c, id)) {
        g << "INDEPENDIZADO: " << id << endl;
    } else {
        if (existeIndependiente(c, id)) {
            g << "YA ERA INDepend.: " << id << endl;
        } else {
            g << "NO INDEPENDIZADO: " << id << endl;
        }
    }
}

// Convierte un evento en dependiente de otro.
// Comprueba que ambos existen, luego llama a hacerDependiente.
// Indica en el fichero si la operación fue posible o imposible.
void hacerDependienteEvento(ifstream& f, ofstream& g, colecInterdep<string, Evento>& c) {
    string id, super;
    getline(f, id);
    getline(f, super);
    if (existe(c, id) && existe(c, super)) {
        g << "INTENTANDO hacer depend.: " << id << " -de-> " << super << endl;
        hacerDependiente(c, id, super);
    } else {
        g << "IMPOSIBLE hacer depend.: " << id << " -de-> " << super << endl;
    }
}

// Borra un evento de la colección.
// Solo borra si no tiene dependientes. Escribe en el fichero si se ha borrado o no.
void borrarEvento(ifstream& f, ofstream& g, colecInterdep<string, Evento>& c) {
    string id;
    getline(f, id);
    if (borrar(c, id)) {
        g << "BORRADO: " << id << endl;
    } else {
        g << "NO BORRADO: " << id << endl;
    }
}

//Lista todos los eventos que dependen de un identificador dado.
//Muestra la información del evento padre y sus dependientes.
//Recorre toda la colección con iterador interno para buscar hijos
void listarDependientes(ifstream& f, ofstream& g, colecInterdep<string, Evento>& c) {
    string id;
    getline(f, id);
    Evento eventoPadre;
    bool esDepPadre;
    string superPadre;
    unsigned int numDepPadre; 
    g << "****DEPENDIENTES: " << id << endl;
    if (!obtenerInfo(c, id, eventoPadre, esDepPadre, superPadre, numDepPadre)) {
        g << "****DESCONOCIDO" << endl;
        return; 
    }
    string descPadre = descripcion(eventoPadre);
    int prioPadre = prioridad(eventoPadre);

    if (esDepPadre) {
        g << "[ " << id << " -de-> " << superPadre << " ;;; " << numDepPadre << " ] --- "
          << descPadre << " --- ( " << prioPadre << " ) ****" << endl;
    } else {
        g << "[ " << id << " --- " << numDepPadre << " ] --- "
          << descPadre << " --- ( " << prioPadre << " ) ****" << endl;
    }
    iniciarIterador(c);
    unsigned int contadorHijos = 1; 
    while (existeSiguiente(c)) {
        if (siguienteDependiente(c)) {
            string supervisorHijo;
            siguienteSuperior(c, supervisorHijo); 
            if (supervisorHijo == id) {
                string idHijo;
                siguienteIdent(c, idHijo);
                Evento eventoHijo;
                siguienteVal(c, eventoHijo);
                unsigned int numDepHijo; 
                siguienteNumDependientes(c, numDepHijo);
                string descHijo = descripcion(eventoHijo);
                int prioHijo = prioridad(eventoHijo);
                g << "[" << contadorHijos << " -> " << idHijo << " -de-> " << id 
                  << " ;;; " << numDepHijo << " ] --- "
                  << descHijo << " --- ( " << prioHijo << " ) ;;;;" << endl;
                contadorHijos++;
            }
        }
        avanza(c); 
    }
    g << "****FINAL dependientes -de-> " << id << endl;
}

// Lista todos los eventos de la colección.
// Muestra sus identificadores, dependencias y número de dependientes.
// Recorre la colección con iterador interno para mostrar cada elemento.
void listarTodos(ifstream& f, ofstream& g, colecInterdep<string, Evento>& c) {
    g << "-----LISTADO: " << tamanyo(c) << endl;
    iniciarIterador(c);
    while (existeSiguiente(c)) { 
        string id;
        Evento evento;
        unsigned int numDep; 
        
        siguienteIdent(c, id);
        siguienteVal(c, evento);
        siguienteNumDependientes(c, numDep); 
        bool esDep = siguienteDependiente(c); 
        string desc = descripcion(evento);
        int prio = prioridad(evento); 
        if (esDep) {
            string supervisor;
            siguienteSuperior(c, supervisor); 
            g << "[ " << id << " -de-> " << supervisor << " ;;; " << numDep << " ] --- "
              << desc << " --- ( " << prio << " )" << endl;
        } else {
            g << "[ " << id << " --- " << numDep << " ] --- "
              << desc << " --- ( " << prio << " )" << endl;
        }
        avanza(c);
    }
    g << "-----" << endl;
}

// Obtiene información completa de un evento.
// Muestra su descripción, prioridad, dependencias y número de dependientes.
// Devuelve verdadero si se localiza, falso si no existe.
bool obtenerInfoEvento(ifstream& f, ofstream& g, colecInterdep<string, Evento>& coleccion) {
    string id;
    getline(f, id);
    Evento evento;
    bool esDependiente;
    string supervisor;   
    unsigned int numDep;
    if (obtenerInfo(coleccion, id, evento, esDependiente, supervisor, numDep)) {
        string desc = descripcion(evento);
        int prio = prioridad(evento);
        g << "LOCALIZADO: ";
        if (esDependiente) {
            g << "[ " << id << " -de-> " << supervisor << " ;;; " << numDep << " ] --- "
              << desc << " --- ( " << prio << " )" << endl;
        } else {
            g << "[ " << id << " --- " << numDep << " ] --- "
              << desc << " --- ( " << prio << " )" << endl;
        }
        return true; 
    } else {
        g << "NO LOCALIZADO: " << id << endl;
        return false;
    }
}

//Añade un nuevo evento a la colección.
//Lee su identificador, descripción, prioridad y tipo (dependiente o independiente).
//Muestra en el fichero si ha sido introducido o no.
bool anadirNuevoEvento(ifstream &f,ofstream &g, colecInterdep<string, Evento>& coleccion ){
  string id, desc, dep, idSup, salto;
  int prioridad=0;
  getline(f, id);
  getline(f, desc);
  f >> prioridad;
  getline(f, salto);
  getline(f, dep);
  getline(f, idSup);
  Evento evento = crearEvento(desc, prioridad);
  if(dep == "INDependiente"){
    if(anadirIndependiente(coleccion, id, evento)){
      g << "INTRODUCIDO: " << "[ "<< id <<" ] --- "<< desc << " --- ( "<<prioridad<<" )" << endl;
      return true;
    }else{
      g << "NO INTRODUCIDO: " << "[ "<< id <<" ] --- "<< desc << " --- ( "<<prioridad<<" )" << endl;
      return false;
    }
  } else {
    if(anadirDependiente(coleccion, id, evento, idSup)){
      g << "INTRODUCIDO: " << "[ "<< id <<" -de-> "<< idSup <<" ] --- "<< desc << " --- ( "<<prioridad<<" )" << endl;
      return true;
    } else {
      g << "NO INTRODUCIDO: " << "[ "<< id <<" -de-> "<< idSup <<" ] --- "<< desc << " --- ( "<<prioridad<<" )" << endl;
      return false;
    }
  }
}

// Cambia la información de un evento existente.
// Actualiza la descripción y prioridad. Mantiene dependencias y dependientes.
// Informa si el cambio se ha realizado o no.
bool cambiarInfo(ifstream &f,ofstream &g, colecInterdep<string, Evento>& coleccion){
  string nombre, descrip, salto;
  int prioridad = 0;
  unsigned int numDepend;
  getline(f, nombre);
  getline(f, descrip);
  f >> prioridad;
  getline(f, salto);
  Evento eventoNuevo = crearEvento(descrip, prioridad);

  Evento eventoAnt;
  bool depen; 
  string nomSup;

  if(obtenerInfo(coleccion, nombre, eventoAnt, depen, nomSup, numDepend)){
    if(actualizarVal(coleccion, nombre, eventoNuevo)){
      if(depen){
        g << "CAMBIADO: " << "[ "<< nombre <<" -de-> "<< nomSup <<" ;;; "<< numDepend<< " ] --- "<< descrip << " --- ( "<<prioridad<<" )" << endl;
        return true;
      }else{
        g << "CAMBIADO: " << "[ "<< nombre << " --- " << numDepend << " ] --- "<< descrip << " --- ( "<<prioridad<<" )" << endl;
        return true;
      }
    }else{
      g << "NO CAMBIADO: "<< nombre << endl;
      return false;
    }
  }else{
    g << "NO CAMBIADO: "<< nombre << endl;
    return false;
  }
}

// Comprueba si un evento existe y si es dependiente o independiente.
// Imprime en el fichero su estado.
void existeEvento(ifstream &f,ofstream &g, colecInterdep<string, Evento>& coleccion){
  string nombre;
  getline(f, nombre);
  if(existe(coleccion, nombre)){
    if(existeDependiente(coleccion, nombre)){
      g << "DEPendiente: "<<  nombre <<  endl;
    }else{
      g << "INDEPendiente: "<< nombre <<  endl;
    }
  }else{
    g << "DESCONOCIDO: "<< nombre << endl;
  }
}

//Inicializa la colección y gestiona el flujo de lectura de instrucciones.
//Abre los ficheros "entrada.txt" y "salida.txt" y procesa línea a línea las instrucciones.
//Llama a las funciones anteriores según la instrucción: añadir, cambiar, borrar, listar, etc.
int main(){
  colecInterdep<string, Evento> coleccion;
  crear(coleccion);
  ifstream f;
  ofstream g;
  f.open("entrada.txt");
  g.open("salida.txt");
  string instruccion;
  string salto;
  if(f.is_open()){
    if(g.is_open()){
      while (f >> instruccion) {
        getline(f,salto);
        if (instruccion == "A"){
          anadirNuevoEvento(f, g, coleccion);
        }else if (instruccion == "C"){
          cambiarInfo(f,g,coleccion);
        }else if (instruccion == "D"){
          hacerDependienteEvento(f, g, coleccion);
        }else if (instruccion == "O"){
          obtenerInfoEvento(f, g, coleccion);
        }else if (instruccion == "E"){
          existeEvento(f,g,coleccion);
        }else if (instruccion == "I"){
          hacerIndependienteEvento(f,g,coleccion);
        }else if (instruccion == "B"){
          borrarEvento(f,g,coleccion);
        }else if (instruccion == "LD"){
          listarDependientes(f,g,coleccion);
        }else if (instruccion == "LT"){
          listarTodos(f,g,coleccion);
        }
      } 
    }else{
      cout << "Error al crear el fichero de salida."<<endl;
    }
  }else{
    cout << "Error al abrir fichero de entrada."<< endl;
  }
}