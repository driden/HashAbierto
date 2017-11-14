#ifndef LISTAENCADENADAITERACION_CPP
#define LISTAENCADENADAITERACION_CPP

#include "ListaEncadenadaIteracion.h"


template <class T>
ListaEncadenadaIteracion<T>::ListaEncadenadaIteracion(const ListaEncadenadaImp<T> listaAIterar, nat posicion)
{
	principioLista = listaAIterar;
	this->posicion = posicion;
}

template<class T>
ListaEncadenadaIteracion<T>::ListaEncadenadaIteracion(const ListaEncadenadaImp<T> listaAIterar)
	:principioLista(listaAIterar)	
{
	posicion = 0;
}

template<class T>
bool ListaEncadenadaIteracion<T>::HayElemento() const
{
	return principioLista.Largo() > posicion;
}

template<class T>
const T & ListaEncadenadaIteracion<T>::ElementoActual() const
{
	return principioLista.Obtener(posicion);
}

template<class T>
void ListaEncadenadaIteracion<T>::Avanzar()
{
	posicion++;
}

template<class T>
void ListaEncadenadaIteracion<T>::Reiniciar()
{
	posicion = 0;
}

template <class T>
Puntero<Iteracion<T>> ListaEncadenadaIteracion<T>::Clonar() const
{
	return new ListaEncadenadaIteracion(*this);
}


#endif

