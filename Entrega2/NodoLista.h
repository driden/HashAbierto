#pragma once
///  Esta clase modela el nodo de una lista simplemente encadenada
#include "Puntero.h"
template <class T>
struct NodoLista
{
	T _data;
	Puntero<NodoLista<T>> _sig;
};