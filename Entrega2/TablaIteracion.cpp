#include <thr/xthrcommon.h>
#ifndef TABLAITERACION_H
#define TABLAITERACION_H

#include "TablaIteracion.h"

template <class K, class V>
TablaIteracion<K, V>::TablaIteracion(const HashAbiertoImpl<K, V>& abierto) :
	hashAbierto(abierto)
{
	cubetas = abierto.CubetasOcupadas();
	principio = cubetas;
	iteradorCubeta = cubetas->ObtenerIterador();
	nat cubeta = iteradorCubeta.HayElemento() ? iteradorCubeta.ElementoActual() : 0;
	posicion = Tupla<nat, nat>(cubeta, 0);
}

template <class K, class V>
bool TablaIteracion<K, V>::HayElemento() const
{
	return hashAbierto.CanGet(posicion);
}

template <class K, class V>
const Tupla<K, V>& TablaIteracion<K, V>::ElementoActual() const
{
	assert(hashAbierto.CanGet(posicion));

	return hashAbierto.Get(posicion);
}

template <class K, class V>
void TablaIteracion<K, V>::Avanzar()
{
	posicion.AsignarDato2(posicion.Dato2 + 1);
	if (!hashAbierto.CanGet(posicion))
	{
		iteradorCubeta.Avanzar();
		if (iteradorCubeta.HayElemento())
		{
			posicion.AsignarDato1(iteradorCubeta.ElementoActual());
			posicion.AsignarDato2(0);
		}
	}
}

template <class K, class V>
void TablaIteracion<K, V>::Reiniciar()
{
	iteradorCubeta.Reiniciar();
	
	if (iteradorCubeta.HayElemento())
	{
		posicion.AsignarDato1(iteradorCubeta.ElementoActual());
		posicion.AsignarDato2(0);
	}
}

#endif
