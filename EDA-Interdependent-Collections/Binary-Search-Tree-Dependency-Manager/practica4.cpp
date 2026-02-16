//*****************************************************************
// File:    main.cpp
// Authors: Anastasia Shlyk (NIP: 931807)
//          Enrique José Guaras Lacasta (NIP: 870709)
// Date:    Noviembre 2025
// Coms:    Practica 3 (EDA)
//*****************************************************************

#include "coleccionesInterdependientes.hpp"
#include "evento.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const string ID_VACIO = "-.-.-.-.-";

void hacerIndependienteEvento(ifstream &f, ofstream &g,
                              colecInterdep<string, Evento> &c) {
  string id;
  getline(f, id);
  if (existeDependiente(c, id)) {
    hacerIndependiente(c, id);
    g << "INDEPENDIZADO: " << id << endl;
  } else if (existeIndependiente(c, id)) {
    g << "YA ERA INDepend.: " << id << endl;
  } else {
    g << "NO INDEPENDIZADO: " << id << endl;
  }
}

void hacerDependienteEvento(ifstream &f, ofstream &g,
                            colecInterdep<string, Evento> &c) {
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

void borrarEvento(ifstream &f, ofstream &g, colecInterdep<string, Evento> &c) {
  string id;
  getline(f, id);
  unsigned int numDep;
  obtenerNumDependientes(c, id, numDep);
  if (existe(c, id) && numDep == 0) {
    borrar(c, id);
    g << "BORRADO: " << id << endl;
  } else {
    g << "NO BORRADO: " << id << endl;
  }
}

void listarDependientes(ifstream &f, ofstream &g,
                        colecInterdep<string, Evento> &c) {
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
  unsigned int prioPadre = prioridad(eventoPadre);
  if (esDepPadre) {
    g << "[ " << id << " -de-> " << superPadre << " ;;; " << numDepPadre
      << " ] --- " << descPadre << " --- ( " << prioPadre << " ) ****" << endl;
  } else {
    g << "[ " << id << " --- " << numDepPadre << " ] --- " << descPadre
      << " --- ( " << prioPadre << " ) ****" << endl;
  }
  iniciarIterador(c);
  int contadorHijos = 1;
  while (existeSiguiente(c)) {
    if (siguienteDependiente(c)) {
      string supervisorHijo;
      siguienteSuperior(c, supervisorHijo);
      if (supervisorHijo == id) {
        string idHijo;
        siguienteIdent(c, idHijo);

        Evento eventoHijo;
        siguienteVal(c, eventoHijo);

        int numDepHijo;
        siguienteNumDependientes(c, numDepHijo);

        string descHijo = descripcion(eventoHijo);
        unsigned int prioHijo = prioridad(eventoHijo);

        g << "[" << contadorHijos << " -> " << idHijo << " -de-> " << id
          << " ;;; " << numDepHijo << " ] --- " << descHijo << " --- ( "
          << prioHijo << " ) ;;;;" << endl;

        contadorHijos++;
      }
    }
    avanza(c);
  }
  g << "****FINAL dependientes -de-> " << id << endl;
}

void listarTodos(ifstream &f, ofstream &g, colecInterdep<string, Evento> &c) {
  g << "-----LISTADO: " << tamanyo(c) << endl;
  iniciarIterador(c);
  while (existeSiguiente(c)) {

    string id;
    Evento evento;
    int numDep;
    siguienteIdent(c, id);
    siguienteVal(c, evento);
    siguienteNumDependientes(c, numDep);
    bool esDep = siguienteDependiente(c);
    string desc = descripcion(evento);
    unsigned int prio = prioridad(evento);
    if (esDep) {
      string supervisor;
      siguienteSuperior(c, supervisor);
      g << "[ " << id << " -de-> " << supervisor << " ;;; " << numDep
        << " ] --- " << desc << " --- ( " << prio << " )" << endl;
    } else {
      g << "[ " << id << " --- " << numDep << " ] --- " << desc << " --- ( "
        << prio << " )" << endl;
    }
    avanza(c);
  }
  g << "-----" << endl;
}

bool obtenerInfoEvento(ifstream &f, ofstream &g,
                       colecInterdep<string, Evento> &coleccion) {
  string id;
  getline(f, id);
  Evento evento;
  bool esDependiente;
  string supervisor;
  unsigned int numDep;
  if (obtenerInfo(coleccion, id, evento, esDependiente, supervisor, numDep)) {
    string desc = descripcion(evento);
    unsigned int prio = prioridad(evento);
    g << "LOCALIZADO: ";
    if (esDependiente) {
      g << "[ " << id << " -de-> " << supervisor << " ;;; " << numDep
        << " ] --- " << desc << " --- ( " << prio << " )" << endl;
    } else {
      g << "[ " << id << " --- " << numDep << " ] --- " << desc << " --- ( "
        << prio << " )" << endl;
    }
    return true;
  } else {
    g << "NO LOCALIZADO: " << id << endl;
    return false;
  }
}

bool anadirNuevoEvento(ifstream &f, ofstream &g,
                       colecInterdep<string, Evento> &coleccion) {
  string id, desc, dep, idSup, salto;
  int prioridad = 0;
  getline(f, id);
  getline(f, desc);
  f >> prioridad;
  getline(f, salto);
  getline(f, dep);
  getline(f, idSup);
  Evento evento = crearEvento(desc, prioridad);
  if (existe(coleccion, id)) {
    if (dep == "INDependiente") {
      g << "NO INTRODUCIDO: "
        << "[ " << id << " ] --- " << desc << " --- ( " << prioridad << " )"
        << endl;
      return false;
    } else {
      g << "NO INTRODUCIDO: "
        << "[ " << id << " -de-> " << idSup << " ] --- " << desc << " --- ( "
        << prioridad << " )" << endl;
      return false;
    }
  } else {
    if (dep == "INDependiente") {
      anadirIndependiente(coleccion, id, evento);
      g << "INTRODUCIDO: "
        << "[ " << id << " ] --- " << desc << " --- ( " << prioridad << " )"
        << endl;
      return true;
    } else if (dep == "DEPendiente") {
      anadirDependiente(coleccion, id, evento, idSup);
      if (existeDependiente(coleccion, id)) {
        g << "INTRODUCIDO: "
          << "[ " << id << " -de-> " << idSup << " ] --- " << desc << " --- ( "
          << prioridad << " )" << endl;
        return true;
      } else {
        g << "NO INTRODUCIDO: "
          << "[ " << id << " -de-> " << idSup << " ] --- " << desc << " --- ( "
          << prioridad << " )" << endl;
        return false;
      }
    }
    return false;
  }
}

bool cambiarInfo(ifstream &f, ofstream &g,
                 colecInterdep<string, Evento> &coleccion) {
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

  if (obtenerInfo(coleccion, nombre, eventoAnt, depen, nomSup, numDepend)) {
    if (actualizarVal(coleccion, nombre, eventoNuevo)) {
      if (depen) {
        g << "CAMBIADO: "
          << "[ " << nombre << " -de-> " << nomSup << " ;;; " << numDepend
          << " ] --- " << descrip << " --- ( " << prioridad << " )" << endl;
        return true;
      } else {
        g << "CAMBIADO: "
          << "[ " << nombre << " --- " << numDepend << " ] --- " << descrip
          << " --- ( " << prioridad << " )" << endl;
        return true;
      }
    } else {
      g << "NO CAMBIADO: " << nombre << endl;
      return false;
    }
  } else {
    g << "NO CAMBIADO: " << nombre << endl;
    return false;
  }
}

void existeEvento(ifstream &f, ofstream &g,
                  colecInterdep<string, Evento> &coleccion) {
  string nombre;
  getline(f, nombre);
  if (existe(coleccion, nombre)) {
    if (existeDependiente(coleccion, nombre)) {
      g << "DEPendiente: " << nombre << endl;
    } else {
      g << "INDEPendiente: " << nombre << endl;
    }
  } else {
    g << "DESCONOCIDO: " << nombre << endl;
  }
}

int main() {
  colecInterdep<string, Evento> coleccion;
  crear(coleccion);

  ifstream f;
  ofstream g;
  f.open("entrada.txt");
  g.open("salida.txt");
  string instruccion;
  string salto;
  if (f.is_open()) {
    if (g.is_open()) {
      while (f >> instruccion) {
        getline(f, salto);
        if (instruccion == "A") {
          anadirNuevoEvento(f, g, coleccion);
        } else if (instruccion == "C") {
          cambiarInfo(f, g, coleccion);
        } else if (instruccion == "D") {
          hacerDependienteEvento(f, g, coleccion);
        } else if (instruccion == "O") {
          obtenerInfoEvento(f, g, coleccion);
        } else if (instruccion == "E") {
          existeEvento(f, g, coleccion);
        } else if (instruccion == "I") {
          hacerIndependienteEvento(f, g, coleccion);
        } else if (instruccion == "B") {
          borrarEvento(f, g, coleccion);
        } else if (instruccion == "LD") {
          listarDependientes(f, g, coleccion);
        } else if (instruccion == "LT") {
          listarTodos(f, g, coleccion);
        }
      }
    } else {
      cout << "Error al crear el fichero de salida." << endl;
    }
  } else {
    cout << "Error al abrir fichero de entrada." << endl;
  }
}