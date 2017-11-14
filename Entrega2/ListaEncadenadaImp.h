#pragma once

#include "ListaOrd.h"
#include "NodoLista.h"

template <class T>
class ListaEncadenadaImp :
	public ListaOrd<T>
{
private:
	Puntero<NodoLista<T>> lista;
	nat cantidadElementos;
	Comparador<T> comparador;

	// PRE: 
	// POS: Crea una instancia de ListaEncadenadaImp, usado para clonar
	ListaEncadenadaImp(const Puntero<NodoLista<T>>& aClonar, nat& cantidadElem, Comparador<T> comp);

	// Clona la lista recursivamente
	// PRE:
	// POS: se genera una copia de la lista aClonar en memoria
	typename Puntero<NodoLista<T>> ListaEncadenadaImp<T>::ClonRecursivo(const Puntero<NodoLista<T>>& aClonar, nat& cantidadElem) const;

public:
	~ListaEncadenadaImp() { //lista = nullptr;
		}

	// PRE: -
	// POS: Crea una ListaEncadenadaImp a partir de un comparador, toma el comparador por defecto
	//		si no se le provee uno
	ListaEncadenadaImp(Comparador<T> comp = Comparador<T>::Default);

	// PRE: Está ordenada
	// POS: e pertenece a la lista. La lista está ordenada y contiene todos los elementos que había en la lista antes de la inserción
	void InsertarOrdenado(const T& e) override;

	// PRE: La lista no está vacía
	// POS: Retorna el primer elemento de la lista
	const T& Cabeza() const override;

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
	// POS: Retorna true si y solo si la lista esta vacia
	bool EstaVacia() const override;

	// PRE: -
	// POS: Retorna un clon de la lista que no comparte memoria con ella
	Puntero<ListaOrd<T>> Clon() const override;

	// PRE: -
	// POS: Retorna un iterador de la lista
	Iterador<T> ObtenerIterador() const override;	
};

#include "ListaEncadenadaImp.cpp"