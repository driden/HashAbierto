#include <corecrt_memcpy_s.h>
#ifndef HASH_CERRADO_ITERACION_CPP
#define HASH_CERRADO_ITERACION_CPP

#include "HashCerradoIteracion.h"


template <class K, class V>
HashCerradoIteracion<K, V>::HashCerradoIteracion(const HashCerradoImpl<K, V>& hashCerrado):
hash(hashCerrado)
{
	celdasOcupadas = hashCerrado.celdas_ocupadas();
	iter = celdasOcupadas->ObtenerIterador();

	pos = iter.HayElemento() ? iter.ElementoActual() : 0;
}

template <class K, class V>
bool HashCerradoIteracion<K, V>::HayElemento() const
{
	return iter.HayElemento();
}

template <class K, class V>
const Tupla<K, V>& HashCerradoIteracion<K, V>::ElementoActual() const
{
	return hash.get(iter.ElementoActual());
}

template <class K, class V>
void HashCerradoIteracion<K, V>::Avanzar()
{
	iter.Avanzar();
}

template <class K, class V>
void HashCerradoIteracion<K, V>::Reiniciar()
{
	iter.Reiniciar();
}
#endif
