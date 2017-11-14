#pragma once
#include "Comparacion.h"
#include "Tupla.h"

template <class K, class V>
class ComparacionTuplaKV : Comparacion<Tupla<K,V>>
{
private:
	Comparador<K> comp;
public:
	~ComparacionTuplaKV(){}
	ComparacionTuplaKV(Comparador<K> comparadorClave);

	CompRetorno Comparar(const Tupla<K, V>& t1, const Tupla<K, V>& t2) const override;
};

#include "ComparacionTuplaKV.cpp"
