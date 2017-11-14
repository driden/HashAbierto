#pragma once

#include "Iterable.h"
#include "ListaEncadenadaImp.h"

template <class T>
class ListaEncadenadaIteracion: public Iteracion<T>
{
private:
	const ListaEncadenadaImp<T> principioLista;	
	nat posicion;

	// PRE: - 
	// POS: Constructor usado para clonacion, recibe una instancia de ListaEncadenadaImp y una posicion
	ListaEncadenadaIteracion(const ListaEncadenadaImp<T> listaAIterar, nat posicion);
public:
	~ListaEncadenadaIteracion() {}
	
	// PRE:
	// POS: crea una instancia de ListaEncadenadaIteracion, recibe la lista a iterar 
	ListaEncadenadaIteracion(const ListaEncadenadaImp<T> listaAIterar);

	// PRE:
	// POS: retorna true si hay un elemento para iterar.
	bool HayElemento() const override;

	// PRE:
	// POS: Devuelve el elemento sobre el cual se itera.
	const T& ElementoActual() const override;

	// PRE:
	// POS: avanza el iterador.
	void Avanzar() override;

	// PRE:
	// POS: reinicia el iterador
	void Reiniciar() override;

	// PRE:
	// POS: clona la iteracion sin compartir memoria.
	Puntero<Iteracion<T>> Clonar() const override;

};

#include "ListaEncadenadaIteracion.cpp"

