#pragma once
#include "NodoTabla.h"

template <class K, class V>
class NodoTablaComparacion : public Comparacion<NodoTabla<K,V>>
{
public:
	CompRetorno Comparar(const NodoTabla<K, V>& t1, const NodoTabla<K, V>& t2) const override;
};

#include "NodoTablaComparacion.cpp"