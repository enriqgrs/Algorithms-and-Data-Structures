//*****************************************************************
// File:    evento.cpp
// Authors: Anastasia Shlyk
//          Enrique José Guaras Lacasta
// Date:    Noviembre 2025
// Coms:    Practica 3 (EDA)
//*****************************************************************

#include "evento.hpp"
#include <string>
#include <iostream>
using namespace std;

//Devuelve un evento compuesto con descripción descrip y con prioridad prio.
Evento crearEvento(const string descrip, const int prio){
  Evento nuevo;
  nuevo.descripcion = descrip;
  nuevo.prioridad = prio;
  return nuevo;
}

// Dado un evento e formado como (D,P) devuelve la cadena D, i.e. la descripción en el evento e.
string descripcion(Evento& e){
  return e.descripcion;
}

// Dado un evento e formado como (D,P) devuelve un evento igual al compuesto como (nueva,P).
void cambiarDescripcion(Evento &e, const string nueva){
  e.descripcion = nueva;
}

// Dado un evento e formado como (D,P), devuelve P, i.e. la prioridad en el evento e.
int prioridad(Evento& e){
  return e.prioridad;
}

// Dado un evento e formado como (D,P) y un natural pri, devuelve un evento igual al compuesto como
// (D,pri).
void cambiarPrioridad(Evento& e, const int pri){
  e.prioridad = pri;
}

void escribir(Evento &e){
  cout << e.descripcion << " " << e.prioridad << endl;
}

