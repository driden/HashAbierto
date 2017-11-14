#pragma once

#include "Tabla.h"
#include "Array.h"
#include "FuncionHash.h"
#include "ListaOrd.h"
#include "Puntero.h"

enum estado { LIBRE, OCUPADA, BAJA };

template <class K, class V>
class HashCerradoImpl : public Tabla<K, V>
{
private:

	Puntero<FuncionHash<K>> func;
	Array<Tupla<K, V, estado>> table;
	const Comparador<K> &comp;
	Tupla<K, V> tuplaTemporal;
	nat contador;
	// PRE: -
	// POS: Devuelve el primer numero primo que es posterior a num
	const nat siguiente_primo(const nat num);

	// PRE: -
	// POS: Devuelve la primer posicion en la que puedo insertar la clave 
	const nat buscar_posicion_insertar(const K clave);
public:

	~HashCerradoImpl(){}
	HashCerradoImpl(nat cubetas, Puntero<FuncionHash<K>> fHash, const Comparador<K>& comp);
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

	// PRE: -
	// POS: Devuelve una lista con las cubetas ocupadas
	Puntero<ListaOrd<nat>> celdas_ocupadas() const;

	// PRE: -
	// POS: Devuelve la tupla en la posicion pos
	const Tupla<K, V>& get(nat pos) const;
};

#include "HashCerradoImpl.cpp"
