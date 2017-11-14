#ifndef COMPARACION_TUPLA_K_V_H
#define COMPARACION_TUPLA_K_V_H

#include "ComparacionTuplaKV.h"

template <class K, class V>
ComparacionTuplaKV<K, V>::ComparacionTuplaKV(Comparador<K> comparadorClave)
{
	this->comp = comparadorClave;
}


template <class K, class V>
CompRetorno ComparacionTuplaKV<K, V>::Comparar(const Tupla<K, V>& t1, const Tupla<K, V>& t2) const
{
	if (comp.EsMayor(t1.Dato1, t2.Dato1)) return MAYOR;
	if (comp.EsMenor(t1.Dato1, t2.Dato1)) return MENOR;
	if (comp.SonIguales(t1.Dato1, t2.Dato1)) return IGUALES;
	
	assert(false);
	return DISTINTOS;
}


#endif
