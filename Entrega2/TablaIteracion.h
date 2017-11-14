#pragma once
#include "Iteracion.h"
#include "HashAbiertoImpl.h"

template <class K, class V>
class TablaIteracion : public Iteracion<Tupla<K,V>>
{
private:
	Tupla<nat, nat> posicion;
	const HashAbiertoImpl<K, V> &hashAbierto;

	Puntero<Lista<nat>> cubetas;
	Puntero<Lista<nat>> principio;
	Iterador<nat> iteradorCubeta;
	
public:

	~TablaIteracion() { principio = nullptr; }
	TablaIteracion(const HashAbiertoImpl<K,V> &abierto);
	bool HayElemento() const override;
	const Tupla<K, V>& ElementoActual() const override;
	void Avanzar() override;
	void Reiniciar() override;

	
	Puntero<Iteracion<Tupla<K, V>>> Clonar() const { return nullptr; }
	
};

#include "TablaIteracion.cpp"
