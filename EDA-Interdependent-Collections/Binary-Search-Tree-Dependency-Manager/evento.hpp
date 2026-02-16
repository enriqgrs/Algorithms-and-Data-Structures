//*****************************************************************
// File:    evento.hpp
// Authors: Anastasia Shlyk (NIP: 931807)
//          Enrique José Guaras Lacasta (NIP: 870709)
// Date:    Noviembre 2025
// Coms:    Practica 3 (EDA)
//*****************************************************************

#ifndef _EVENTO_HPP
#define _EVENTO_HPP

#include <string>
#include <iostream>
using namespace std;

// Los valores del TAD evento representarán tuplas formadas como: (descripción, prioridad) siendo la descripción una cadena y la prioridad un número natural.
struct Evento;

//Devuelve un evento compuesto con descripción descrip y con prioridad prio.
Evento crearEvento(const string descrip, const unsigned int prio);

// Dado un evento e formado como (D,P) devuelve la cadena D, i.e. la descripción en el evento e.
string descripcion(Evento& e);

// Dado un evento e formado como (D,P) devuelve un evento igual al compuesto como (nueva,P).
void cambiarDescripcion(Evento &e, const string nueva);

// Dado un evento e formado como (D,P), devuelve P, i.e. la prioridad en el evento e.
unsigned int prioridad(Evento& e);

// Dado un evento e formado como (D,P) y un natural pri, devuelve un evento igual al compuesto como
// (D,pri).
void cambiarPrioridad(Evento& e, const int nueva);

struct Evento{
  friend Evento crearEvento(const string descrip, const unsigned int prio);
  friend string descripcion(Evento& e);
  friend void cambiarDescripcion(Evento &e, const string nueva);
  friend unsigned int prioridad(Evento& e);
  friend void cambiarPrioridad(Evento& e, const int nueva);
  friend void escribir(Evento &e);

  private: 
    string descripcion;
    int prioridad;
};

#endif
