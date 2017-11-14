#pragma once

#include "Tabla.h"
#include "ListaEncadenadaImp.h"
#include "Array.h"
#include "FuncionHash.h"

template <class K, class V>
class HashAbiertoImpl : public Tabla<K, V>
{
private:
	Array<Puntero<ListaOrd<Tupla<K, V>>>> table;
	Puntero<FuncionHash<K>> func;
	nat tope, cubetasOcupadas, largo;
	Comparador<K> comparador;
	Comparador<Tupla<K, V>> compTupla;

	const nat siguiente_primo(const nat num);

public:
	HashAbiertoImpl(Puntero<FuncionHash<K>>, nat cantidadRegistros, Comparador<K> comp);
	~HashAbiertoImpl() {}

	/* CONSTRUCTORAS */

	//PRE: T(c) no está definida y la tabla no está llena
	//POS: Define T(c) = v
	void Agregar(const K& c, const V& v) override;

	//PRE: T(c) está definida
	//POS: Borra la asociación ligada a 'c'
	void Borrar(const K& c) override;

	//PRE: - 
	//POS: Borra todas las asociaciones
	void BorrarTodos() override;

	/* PREDICADOS */

	//PRE: - 
	//POS: Retorna true si está vacía, false sino.
	bool EstaVacia() const override;

	//PRE: - 
	//POS: Retorna true si está llena, false sino.
	bool EstaLlena() const override;

	//PRE: - 
	//POS: Retorna true si T(c) está definida, es decir, si la clave c está definida. False sino.
	bool EstaDefinida(const K& c) const override;

	/* SELECTORAS */

	//PRE: T(c) está definida
	//POS: Retorna 'v', tal que T(c) = v
	const V& Obtener(const K& c) const override;

	//PRE: -
	//POS: Retorna el largo de la tabla
	nat Largo() const override;

	//PRE: -
	//POS: Devuelve un clon de la tabla, no comparten memoria
	Puntero<Tabla<K, V>> Clonar() const override;

	// PRE: -
	// POS: Devuelve un iterador de las tuplas de la tabla
	Iterador<Tupla<K, V>> ObtenerIterador() const override;
	//
	// POS: Devuelve un iterador para las coliciones de clave C
	Iterador<Tupla<K, V>> ObtenerIterador(const K &c);

	// PRE: La tabla esta definida en (x,y)
	// POS: retorna una copia de la clave y el valor en (x,y)
	const Tupla<K, V>& Get(const Tupla<nat,nat> posicion) const;

	// PRE: -
	// POS: - retorna true si hay una tupla en la coordenada dada
	bool CanGet(const Tupla<nat, nat> posicion) const;

	// PRE: -
	// POS: - Devuelve una lista ordenada con los numeros de las cubetas ocupadas
	Puntero<ListaOrd<nat>> CubetasOcupadas() const;
};

#include "HashAbiertoImpl.cpp"
