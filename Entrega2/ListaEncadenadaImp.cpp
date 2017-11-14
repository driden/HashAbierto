#ifndef LISTAENCADENADA_CPP
#define LISTAENCADENADA_CPP

#include "ListaEncadenadaImp.h"	
#include "ListaEncadenadaIteracion.h"

template<class T>
ListaEncadenadaImp<T>::ListaEncadenadaImp(Comparador<T> comp) :
	lista(nullptr),
	cantidadElementos(0),
	comparador(comp)
{
}

template<class T>
ListaEncadenadaImp<T>::ListaEncadenadaImp(const Puntero<NodoLista<T>>& aClonar, nat& cantidadElem, Comparador<T> comp) :
	lista(aClonar),
	cantidadElementos(cantidadElem),
	comparador(comp)
{
}

template<class T>
void ListaEncadenadaImp<T>::InsertarOrdenado(const T & e)
{
	Puntero<NodoLista<T>> nodo = new NodoLista<T>{ e, nullptr };

	if (lista == nullptr) {
		lista = nodo;
	}
	else {
		// Hay al menos un nodo en la lista
		Puntero<NodoLista<T>> iter = lista, anterior = lista;

		// Busco hasta que encuentro un elemento menor al que tengo		
		while (iter && (comparador.EsMayor(e, iter->_data) || comparador.SonIguales(e, iter->_data))) {
			anterior = iter;
			iter = iter->_sig;
		}

		// Discrimino el caso de que tenga que ir al principio
		if (iter && (iter == anterior)) { // Comparacion de punteros
			lista = nodo;
			nodo->_sig = iter;
		}
		else if (iter == nullptr && comparador.EsMayor(e, anterior->_data)) {

			// Si iter es el ultimo y 'e' es Mayor que data en iter
			// entonces 'e' va despues de iter
			anterior->_sig = nodo;
		}
		else
		{
			//generico
			anterior->_sig = nodo;
			nodo->_sig = iter;
		}

		// Clean up
		//anterior = nullptr;
		//iter = nullptr;
	}

	cantidadElementos++;
}

template<class T>
const T & ListaEncadenadaImp<T>::Cabeza() const
{
	return lista->_data;
}

template<class T>
void ListaEncadenadaImp<T>::Eliminar(const T & e)
{
	// Tres casos:
	// Primer Elemento para elminar
	// Elemento del medio
	// Ultimo elemento
	// No esta
	Puntero<NodoLista<T>> iter = lista, anterior = lista;

	while (iter && !comparador.SonIguales(e, iter->_data)) {
		anterior = iter;
		iter = iter->_sig;
	}

	// tengo que borrar iter
	//si son el mismo, es el primero
	if (iter && (iter == anterior)) {
		lista = iter->_sig;
		iter->_sig = nullptr;
		//anterior = nullptr;
	}
	else if (iter && iter->_sig == nullptr) {
		// es el ultimo
		anterior->_sig = nullptr;
	}
	else if (iter){
		// caso generico
		anterior->_sig = anterior->_sig->_sig;
	}
	// Si no encontre
	if (iter != nullptr)
	{
		//iter = nullptr;
		cantidadElementos--;
	}	
}

template<class T>
nat ListaEncadenadaImp<T>::Largo() const
{
	return cantidadElementos;
}

template<class T>
const T & ListaEncadenadaImp<T>::Obtener(const nat n) const
{
	nat pos = 0;
	Puntero<NodoLista<T>> iter = lista;
	while (pos < n) {
		iter = iter->_sig;
		pos++;
	}
	T& dato = iter->_data;
	//iter = nullptr;
	return dato;
}

template<class T>
bool ListaEncadenadaImp<T>::Pertenece(const T & e) const
{
	bool pertenece = false;
	Puntero<NodoLista<T>> iter = lista;
	nat pos = 0;
	while (pos < cantidadElementos) {

		if (comparador.SonIguales(iter->_data, e))
			pertenece = true;

		iter = iter->_sig;
		pos++;
	}

	iter = nullptr;
	return pertenece;
}

template<class T>
bool ListaEncadenadaImp<T>::EstaVacia() const
{
	return cantidadElementos == 0;
}

template<class T>
Puntero<NodoLista<T>> ListaEncadenadaImp<T>::ClonRecursivo(const Puntero<NodoLista<T>>& aClonar, nat& cantidadElem) const
{
	if (aClonar == nullptr) {
		return nullptr;
	}

	cantidadElem++;
	Puntero<NodoLista<T>> nodo = new NodoLista<T>{ aClonar->_data, ClonRecursivo(aClonar->_sig, cantidadElem) };

	return nodo;
}

template<class T>
Puntero<ListaOrd<T>> ListaEncadenadaImp<T>::Clon() const
{
	Puntero<NodoLista<T>> iter = lista;
	nat cantidad = 0;
	Puntero<NodoLista<T>> copia = ClonRecursivo(iter, cantidad);

	iter = nullptr;

	Puntero<ListaOrd<T>> copiaLista = new ListaEncadenadaImp<T>(copia, cantidad, comparador);
	return copiaLista;
}

template<class T>
Iterador<T> ListaEncadenadaImp<T>::ObtenerIterador() const
{
	return new ListaEncadenadaIteracion<T>(*this);
}

#endif