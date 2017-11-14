#pragma once

#ifndef LISTA_H
#define LISTA_H

#include "Iterable.h"
#include "Puntero.h"

typedef unsigned int nat;

template <class T>
class Lista abstract : public Iterable<T>
{
public:
	virtual ~Lista() {}
	
	// PRE: Está ordenada
	// POS: e pertenece a la lista. La lista está ordenada y contiene todos los elementos que había en la lista antes de la inserción
	virtual void Insertar(const T& e) abstract;	

	// PRE: -
	// POS: Elimina una ocurrencia del elemento de la lista si existe. De no existir no tiene acción.
	virtual void Eliminar(const T& e) abstract;

	// PRE: -
	// POS: Retorna el largo de la lista
	virtual nat Largo() const abstract;

	// PRE: La lista tiene un elemento en la posición n. 
	// POS: Retorna el elemento que está en esa posición de la lista. El primer elemento empieza en 0.
	virtual const T& Obtener(const nat n) const abstract;

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la lista.
	virtual bool Pertenece(const T& e) const abstract;

	// PRE: -
	// POS: Retorna un clon de la lista que no comparte memoria con ella
	virtual Puntero<Lista<T>> Clon() const abstract;

	// PRE:
	// POS: Retorna un iterador de la lista
	virtual Iterador<T> ObtenerIterador() const abstract;	
};


#endif