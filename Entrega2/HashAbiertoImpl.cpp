#ifndef HASH_ABIERTO_IMPL_CPP_
#define HASH_ABIERTO_IMPL_CPP_

#include "HashAbiertoImpl.h"
#include "ComparacionTuplaKV.h"
#include "TablaIteracion.h"

template <class K, class V>
const nat HashAbiertoImpl<K, V>::siguiente_primo(const nat num)
{
	const Array<nat> primos(6);
	primos[0] = 2;
	primos[1] = 3;
	primos[2] = 5;
	primos[3] = 7;
	primos[4] = 11;
	primos[5] = 13;

	nat start = (num % 2 == 0) ? num + 3 : num + 2;
	if (start < 80001) start = 80001;

	for (nat n = start; n < 700000; n += 2)
	{
		bool esPrimo = true;

		for (nat q = 0; q < primos.Largo; q++)
		{
			if ((n % primos[q]) == 0)
			{
				esPrimo = false;
				break;
			}
		}

		if (esPrimo) return n;
	}

	// No deberia llegar a este lugar
	assert(false);
	return 0;
}

template <class K, class V>
HashAbiertoImpl<K, V>::HashAbiertoImpl(Puntero<FuncionHash<K>> f, nat cantidadRegistros, Comparador<K> comp)
{
	func = f;
	const nat scope = static_cast<int>(cantidadRegistros*1.7);
	table = Array<Puntero<ListaOrd<Tupla<K, V>>>>(siguiente_primo(scope), nullptr);
	comparador = comp;

	this->compTupla = Comparador<Tupla<K, V>>(new ComparacionTuplaKV<K, V>(comp));

	cubetasOcupadas = 0;
	largo = 0;
}

template <class K, class V>
void HashAbiertoImpl<K, V>::Agregar(const K& c, const V& v)
{
	nat cubeta = func->CodigoDeHash(c);

	float ocupacion = static_cast<float>(cubetasOcupadas) / table.Largo;

	if (ocupacion > 0.7) // re-hashing
	{
		Array<Puntero<ListaOrd<Tupla<K, V>>>> nuevaTable(static_cast<nat>(table.Largo*1.7));
		Array<Puntero<ListaOrd<Tupla<K, V>>>>::Copiar(table, nuevaTable, 0);
		table = nuevaTable;
	}

	Tupla<K, V> tupla(c, v);


	if (table[cubeta] == nullptr)
	{
		table[cubeta] = new ListaEncadenadaImp<Tupla<K, V>>(compTupla);
		cubetasOcupadas++;		
	}
	
	table[cubeta]->InsertarOrdenado(tupla);
	largo++;
}

template <class K, class V>
void HashAbiertoImpl<K, V>::Borrar(const K& c)
{
	assert(EstaDefinida(c));

	nat cubeta = func->CodigoDeHash(c);
	nat largoCubeta = table[cubeta]->Largo();
	table[cubeta]= nullptr;

	largo-=largoCubeta;

	if (table[cubeta] == nullptr) cubetasOcupadas--;
}

template <class K, class V>
void HashAbiertoImpl<K, V>::BorrarTodos()
{
	for (nat i = 0; i < table.Largo; i++)
	{
		table[i] = nullptr;
		cubetasOcupadas = 0;
		largo = 0;
	}
}

template <class K, class V>
bool HashAbiertoImpl<K, V>::EstaVacia() const
{
	return largo == 0;
}

template <class K, class V>
bool HashAbiertoImpl<K, V>::EstaDefinida(const K& c) const
{
	nat cubeta = func->CodigoDeHash(c);

	return table[cubeta] != nullptr;
}

template <class K, class V>
const V& HashAbiertoImpl<K, V>::Obtener(const K& c) const
{
	assert(EstaDefinida(c));

	nat cubeta = func->CodigoDeHash(c);
	Tupla<K, V> t(c, V());

	Iterador<Tupla<K, V>> it = table[cubeta]->ObtenerIterador();

	while (it.HayElemento())
	{
		if (compTupla.SonIguales(t, it.ElementoActual()))
			return it.ElementoActual().Dato2;
	}

	assert(false);
	return table[cubeta]->Obtener(0).Dato2;
}

template <class K, class V>
nat HashAbiertoImpl<K, V>::Largo() const
{
	return this->largo;
}

template <class K, class V>
bool HashAbiertoImpl<K, V>::EstaLlena() const
{
	// La considero llena si la cantidad de cubetas 
	// ocupadas son mayores al 70% de la capacidad

	return cubetasOcupadas > table.Largo*0.7;
}

template <class K, class V>
Puntero<Tabla<K, V>> HashAbiertoImpl<K, V>::Clonar() const
{
	return nullptr;
}

template <class K, class V>
Iterador<Tupla<K, V>> HashAbiertoImpl<K, V>::ObtenerIterador() const
{
	//	return new TablaIteracion<K,V>(*this);

	int aux = 0;
	Array<Tupla<K, V>> arrayIter = Array<Tupla<K, V>>(this->largo);
	// Iterador de Array
	Iterador<Puntero<ListaEncadenadaImp<Tupla<K, V>>>> it = this->table.ObtenerIterador();

	while (it.HayElemento()) {
		Puntero<ListaEncadenadaImp<Tupla<K, V>>> lista = it.ElementoActual();

		// El actual no puede ser nulo
		if (lista != nullptr) {
			Iterador<Tupla<K, V>> iterLista = lista->ObtenerIterador();

			while (iterLista.HayElemento()) {
				arrayIter[aux] = iterLista.ElementoActual();
				aux++;
				iterLista.Avanzar();
			}
		}
		it.Avanzar();
	}
	return arrayIter.ObtenerIterador();
}

template <class K, class V>
Iterador<Tupla<K, V>> HashAbiertoImpl<K, V>::ObtenerIterador(const K& c)
{
	nat cubeta = func->CodigoDeHash(c);
	return table[cubeta]->ObtenerIterador();
}

template <class K, class V>
const Tupla<K, V>& HashAbiertoImpl<K, V>::Get(const Tupla<nat, nat> posicion) const
{
	assert(CanGet(posicion));

	return table[posicion.Dato1]->Obtener(posicion.Dato2);
}

template <class K, class V>
bool HashAbiertoImpl<K, V>::CanGet(const Tupla<nat, nat> posicion) const
{
	return table[posicion.Dato1] && (table[posicion.Dato1])->Largo() > posicion.Dato2;
}

template <class K, class V>
Puntero<ListaOrd<nat>> HashAbiertoImpl<K, V>::CubetasOcupadas() const
{
	Puntero<ListaOrd<nat>> ocupadas = new ListaEncadenadaImp<nat>(Comparador<nat>::Default);

	for (nat i = 0; i < table.Largo; i++)
	{
		if (table[i])
			ocupadas->InsertarOrdenado(i);
	}

	return ocupadas;
}


#endif
