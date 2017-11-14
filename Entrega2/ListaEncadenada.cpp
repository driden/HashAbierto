#ifndef LISTA_ENCADENADA_CPP
#define LISTA_ENCADENADA_CPP

#include "ListaEncadenada.h"

template <class T>
ListaEncadenada<T>::ListaEncadenada(const Comparador<T>& comparador)
{
	this->comp = comparador;
	this->largo = 0;
	this->principio = nullptr;
	this->ultimo = nullptr;
}

template <class T>
void ListaEncadenada<T>::Insertar(const T& e)
{
	Puntero<Nodo<T>> nuevoNodo = new Nodo<T>(e);
	
	if(principio == nullptr)
	{
		principio = nuevoNodo;
		ultimo = principio;
	}
	else
	{
		ultimo->sig = nuevoNodo;
		ultimo = ultimo->sig;
	}

	largo++;
}

template <class T>
void ListaEncadenada<T>::Eliminar(const T& e)
{
	Puntero<Nodo<T>> it = principio;
	Puntero<Nodo<T>> anterior = it;

	while (it != nullptr && !comp.SonIguales(e, it->data))
	{
		anterior = it;
		it = it->sig;
	}

	if (anterior == it)
	{
		principio = principio->sig;
	}
	else
	{
		if (comp.SonIguales(it->data, ultimo->data))
			ultimo = anterior;
		anterior->sig = it->sig;
	}
	largo--;
}

template <class T>
nat ListaEncadenada<T>::Largo() const
{
	return largo;
}

template <class T>
const T& ListaEncadenada<T>::Obtener(const nat n) const
{
	Puntero<Nodo<T>> it = principio;
	
	for (nat i = 0; i < n; i++)
		it = it->sig;

	return it->data;
}

template <class T>
bool ListaEncadenada<T>::Pertenece(const T& e) const
{
	Puntero<Nodo<T>> it = principio;
	
	while (it != nullptr && !comp.SonIguales(e, it->data))
	{
		it = it->sig;
	}

	return it != nullptr;
}

template <class T>
Iterador<T> ListaEncadenada<T>::ObtenerIterador() const
{
	Array<T> arrIt(largo);
	Puntero<Nodo<T>> it = principio;
	
	for (nat i = 0; i < largo; i++)
	{
		arrIt[i] = it->data;
		it = it->sig;
	}

	return arrIt.ObtenerIterador();
}


template <class T>
Puntero<Lista<T>> ListaEncadenada<T>::Clon() const
{
	return nullptr;
}
#endif
