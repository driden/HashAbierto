#pragma once
#include "Puntero.h"
#include "Lista.h"
#include "Tupla.h"

template <class K, class V>
class NodoTabla
{
public:
	Tupla<K,Puntero<Lista<V>>> keyValues;
	Puntero<Tupla<K, Puntero<Lista<V>>>> sig;

	NodoTabla(K key, Puntero<Lista<V>> values)
	{
		keyValues = Tupla<K, Puntero<Lista<V>>>(key, values);
		sig = nullptr;
	}

	NodoTabla()
	{

	}

	K Key() const
	{
		return keyValues.Dato1;
	}

	Puntero<Lista<V>> Values() const
	{
		return keyValues.Dato2;
	}
};
