
#ifndef HASH_ABIERTO_IMPL_CPP_
#define HASH_ABIERTO_IMPL_CPP_

#include "HashAbiertoImpl.h"
#include "ComparacionTuplaKV.h"
#include "TablaIteracion.h"
#include "ListaEncadenada.h"

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

	table = Array<Puntero<Lista<NodoTabla<K, V>>>>(siguiente_primo(scope), nullptr);
	compClave = comp;
	compValor = Comparador<V>::Default;

	this->compTupla = Comparador<Tupla<K, V>>(new ComparacionTuplaKV<K, V>(comp));

	cubetasOcupadas = 0;
	largo = 0;
}

template <class K, class V>
int HashAbiertoImpl<K, V>::GetCubeta(const K& c) const
{
	return func->CodigoDeHash(c) % table.Largo;
}

template <class K, class V>
void HashAbiertoImpl<K, V>::Agregar(const K& c, const V& v)
{
	nat cubeta = GetCubeta(c);

	float ocupacion = static_cast<float>(cubetasOcupadas) / table.Largo;
	//re hashing
	if (ocupacion > 0.7) // re-hashing
	{
		Array<Puntero<Lista<NodoTabla<K, V>>>> nuevaTable(static_cast<nat>(table.Largo*1.7));
		Array<Puntero<Lista<NodoTabla<K, V>>>>::Copiar(table, nuevaTable, 0);
		table = nuevaTable;
	}
	// Lista vacia si no hay nada en la cubeta
	if (table[cubeta] == nullptr)
	{
		Puntero<Lista<V>> l = new ListaEncadenada<V>(compValor);
		NodoTabla<K, V> nodoT(c, l);

		Puntero<Lista<NodoTabla<K, V>>> lTabla = new ListaEncadenada<NodoTabla<K, V>>();
		lTabla->Insertar(nodoT);

		table[cubeta] = lTabla;
		cubetasOcupadas++;
	}

	Puntero<Lista<NodoTabla<K, V>>> listaClavesValores = table[cubeta];
	Iterador<NodoTabla<K, V>> it = listaClavesValores->ObtenerIterador();
	while (it.HayElemento())
	{
		NodoTabla<K, V> actual = it.ElementoActual();

		if (compClave.SonIguales(actual.keyValues.Dato1, c))
		{
			Puntero<Lista<V>> pLista = actual.keyValues.Dato2;
			if (!pLista->Pertenece(v))
			{
				pLista->Insertar(v);
				largo++;
			}
			return;
		}
		it.Avanzar();
	}

	// Si la clave todavia no esta en la lista de la cubeta
	Puntero<Lista<V>> l = new ListaEncadenada<V>(compValor);
	l->Insertar(v);
	NodoTabla<K, V> nodoT(c, l);
	listaClavesValores->Insertar(nodoT);
}

template <class K, class V>
void HashAbiertoImpl<K, V>::Borrar(const K& c)
{
	assert(EstaDefinida(c));
	nat cubeta = GetCubeta(c);
	Puntero<Lista<NodoTabla<K, V>>> lista = table[cubeta];
	//Chequea que la clave a borrar sea la correcta
	assert(compClave.SonIguales(lista->Obtener(0).keyValues.Dato1, c));

	const nat largoCubeta = lista->Largo();

	table[cubeta] = nullptr;
	largo -= largoCubeta;
	cubetasOcupadas--;
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
	const nat cubeta = GetCubeta(c);

	Puntero<Lista<NodoTabla<K, V>>> lista = table[cubeta];

	if (!lista) return false;

	Iterador<NodoTabla<K, V>> it = lista->ObtenerIterador();
	while (it.HayElemento())
	{
		NodoTabla<K, V> actual = it.ElementoActual();
		if (compClave.SonIguales(actual.keyValues.Dato1, c))
		{
			return true;
		}
		it.Avanzar();
	}
	return false;
}

template <class K, class V>
const V& HashAbiertoImpl<K, V>::Obtener(const K& c) const
{
	assert(EstaDefinida(c));

	const nat cubeta = GetCubeta(c);

	Puntero<Lista<NodoTabla<K, V>>> t = table[cubeta];
	Iterador<NodoTabla<K, V>> it = t->ObtenerIterador();

	while (it.HayElemento())
	{
		NodoTabla<K, V> actual = it.ElementoActual();
		if (compClave.SonIguales(actual.keyValues.Dato1, c))
		{
			Puntero<Lista<V>> pLista = actual.keyValues.Dato2;
			return pLista->Obtener(0);
		}
		it.Avanzar();
	}

	return *(new V());
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
	// Array<Puntero<Lista<NodoTabla<K,V>>>>
	Iterador<Puntero<Lista<NodoTabla<K, V>>>> it = this->table.ObtenerIterador();

	while (it.HayElemento()) {
		Puntero<Lista<NodoTabla<K, V>>> lista = it.ElementoActual();
		it.Avanzar();

		if (!lista) continue;
		NodoTabla<K, V> nodo = lista->Obtener(0);
		K clave = nodo.Key();
		Puntero<Lista<V>> listaV = nodo.Values();
		Iterador<V> iterLista = nodo.Values()->ObtenerIterador();

		while (iterLista.HayElemento()) {
			Tupla<K, V> tupla(clave, iterLista.ElementoActual());
			arrayIter[aux] = tupla;
			aux++;
			iterLista.Avanzar();
		}
	}
	return arrayIter.ObtenerIterador();
}

template <class K, class V>
Iterador<Tupla<K, V>> HashAbiertoImpl<K, V>::ObtenerIterador(const K& c)
{
	assert(EstaDefinida(c));

	Array<Tupla<K, V>> arrayIter;
	Puntero<Lista<NodoTabla<K, V>>> lista = table[GetCubeta(c)];

	// El actual no puede ser nulo
	if (lista != nullptr)
	{
		Iterador<NodoTabla<K, V>> itNodoTabla = lista->ObtenerIterador();

		while (itNodoTabla.HayElemento())
		{
			NodoTabla<K, V> nodo = itNodoTabla.ElementoActual();
			itNodoTabla.Avanzar();

			if (compClave.SonIguales(c, nodo.Key()))
			{
				Puntero<Lista<V>> listaValores = nodo.Values();
				assert(listaValores); //No puede estar vacia
				arrayIter = Array<Tupla<K, V>>(listaValores->Largo());

				Iterador<V> itV = listaValores->ObtenerIterador();
				nat largo = 0;
				while (itV.HayElemento())
				{
					arrayIter[largo++] = Tupla<K, V>(c, itV.ElementoActual());
					itV.Avanzar();
				}
			}
		}
	}

	return arrayIter.ObtenerIterador();
}

//template <class K, class V>
//const Tupla<K, V>& HashAbiertoImpl<K, V>::Get(const Tupla<nat, nat> posicion) const
//{
//	assert(CanGet(posicion));
//
//	return table[posicion.Dato1]->Obtener(posicion.Dato2);
//}
//
//template <class K, class V>
//bool HashAbiertoImpl<K, V>::CanGet(const Tupla<nat, nat> posicion) const
//{
//	return table[posicion.Dato1] && (table[posicion.Dato1])->Largo() > posicion.Dato2;
//}
//
//template <class K, class V>
//Puntero<Lista<nat>> HashAbiertoImpl<K, V>::CubetasOcupadas() const
//{
//	Puntero<Lista<nat>> ocupadas = new ListaEncadenadaImp<nat>(Comparador<nat>::Default);
//
//	for (nat i = 0; i < table.Largo; i++)
//	{
//		if (table[i])
//			ocupadas->InsertarOrdenado(i);
//	}
//
//	return ocupadas;
//}


#endif
