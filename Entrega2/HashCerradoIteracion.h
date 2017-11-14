#ifndef HASH_CERRADO_ITERACION_H
#define HASH_CERRADO_ITERACION_H

#include "Iteracion.h"
#include "Tupla.h"
#include "ListaOrd.h"
#include "HashCerradoImpl.h"

template <class K, class V>
class HashCerradoIteracion : public Iteracion<Tupla<K,V>>
{
private:
	Puntero<ListaOrd<nat>> celdasOcupadas;
	const HashCerradoImpl<K, V> &hash;
	Iterador<nat> iter;
	nat pos;
public:
	~HashCerradoIteracion(){}
	HashCerradoIteracion(const HashCerradoImpl<K,V> &hashCerrado );

	bool HayElemento() const override;
	const Tupla<K, V>& ElementoActual() const override;
	void Avanzar() override;
	void Reiniciar() override;

	Puntero<Iteracion<Tupla<K, V>>> Clonar() const { return nullptr; }
};

#include "HashCerradoIteracion.cpp"
#endif