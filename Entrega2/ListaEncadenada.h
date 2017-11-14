#pragma once
#include "Lista.h"
#include "Nodo.h"
#include "Array.h"

template <class T>
class ListaEncadenada: public Lista<T>
{
public:
	~ListaEncadenada(){}
	ListaEncadenada(const Comparador<T> &comparador);


	// PRE: Está ordenada
	// POS: e pertenece a la lista. La lista está ordenada y contiene todos los elementos que había en la lista antes de la inserción
	void Insertar(const T& e) override;

	// PRE: -
	// POS: Elimina una ocurrencia del elemento de la lista si existe. De no existir no tiene acción.
	void Eliminar(const T& e) override;

	// PRE: -
	// POS: Retorna el largo de la lista
	nat Largo() const override;

	// PRE: La lista tiene un elemento en la posición n. 
	// POS: Retorna el elemento que está en esa posición de la lista. El primer elemento empieza en 0.
	const T& Obtener(const nat n) const override;

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la lista.
	bool Pertenece(const T& e) const override;

	// PRE: -
	// POS: Retorna un clon de la lista que no comparte memoria con ella
	Puntero<Lista<T>> Clon() const override;

	// PRE:
	// POS: Retorna un iterador de la lista
	Iterador<T> ObtenerIterador() const override;

private:	
	nat largo;
	Puntero<Nodo<T>> principio, ultimo;
	Comparador<T> comp;
};



#include "ListaEncadenada.cpp"
