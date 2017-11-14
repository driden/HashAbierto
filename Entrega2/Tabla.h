#ifndef TABLA_H
#define TABLA_H

#include "Iterable.h"
#include "Puntero.h"
#include "Tupla.h"

typedef unsigned int nat;

template <class C, class V>
class Tabla abstract : public Iterable<Tupla<C,V>>
{
public:

	virtual ~Tabla(){ }

	/* CONSTRUCTORAS */

	//PRE: T(c) no est� definida y la tabla no est� llena
	//POS: Define T(c) = v
	virtual void Agregar(const C& c, const V& v) abstract;

	//PRE: T(c) est� definida
	//POS: Borra la asociaci�n ligada a 'c'
	virtual void Borrar(const C& c) abstract;
	
	//PRE: - 
	//POS: Borra todas las asociaciones
	virtual void BorrarTodos() abstract;

	/* PREDICADOS */

	//PRE: - 
	//POS: Retorna true si est� vac�a, false sino.
	virtual bool EstaVacia() const abstract;

	//PRE: - 
	//POS: Retorna true si est� llena, false sino.
	virtual bool EstaLlena() const abstract;

	//PRE: - 
	//POS: Retorna true si T(c) est� definida, es decir, si la clave c est� definida. False sino.
	virtual bool EstaDefinida(const C& c) const abstract;

	/* SELECTORAS */

	//PRE: T(c) est� definida
	//POS: Retorna 'v', tal que T(c) = v
	virtual const V& Obtener(const C& c) const abstract;

	//PRE: -
	//POS: Retorna el largo de la tabla
	virtual nat Largo() const abstract;

	//PRE: -
	//POS: Devuelve un clon de la tabla, no comparten memoria
	virtual Puntero<Tabla<C, V>> Clonar() const abstract;

	virtual Iterador<Tupla<C,V>> ObtenerIterador() const abstract;	
};

#endif