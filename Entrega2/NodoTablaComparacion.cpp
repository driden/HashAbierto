#ifndef NODO_TABLA_COMPARACION_CPP_
#define NODO_TABLA_COMPARACION_CPP_

#include "NodoTablaComparacion.h"

template <class K, class V>
CompRetorno NodoTablaComparacion<K, V>::Comparar(const NodoTabla<K, V>& t1, const NodoTabla<K, V>& t2) const
{
	return DISTINTOS;
}

#endif