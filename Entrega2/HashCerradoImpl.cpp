#include "HashCerradoIteracion.h"
#ifndef HASH_CERRADO_IMPL_CPP_
#define HASH_CERRADO_IMPL_CPP_

#include "HashCerradoImpl.h"
#include "ListaEncadenadaImp.h"

template <class K, class V>
const nat HashCerradoImpl<K, V>::siguiente_primo(const nat num)
{
	const Array<nat> primos(6);
	primos[0] = 2;
	primos[1] = 3;
	primos[2] = 5;
	primos[3] = 7;
	primos[4] = 11;
	primos[5] = 13;

	nat start = (num % 2 == 0) ? num + 3 : num + 2;
	if (start < 1001) start = 1001;

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
const nat HashCerradoImpl<K, V>::buscar_posicion_insertar(const K clave)
{
	nat pos = func->CodigoDeHash(clave);
	while (table[pos].Dato3 == OCUPADA)
	{
		pos = pos++;
		
		// Con esto me aseguro de hacerlo circular
		pos = pos % table.Largo;
	}

	return pos;
}

template <class K, class V>
HashCerradoImpl<K, V>::HashCerradoImpl(nat cubetas, Puntero<FuncionHash<K>> fHash, const Comparador<K>& comp)
: comp(comp)
{
	func = fHash;
	
	const nat scope = static_cast<int>(cubetas*1.7);
	
	Tupla<K, V, estado> vacia(K(), V(), (LIBRE));
	table = Array<Tupla<K, V, estado>>(siguiente_primo(scope), vacia);

	contador = 0;
}

template <class K, class V>
void HashCerradoImpl<K, V>::Agregar(const K& c, const V& v)
{
	assert(!EstaLlena());

	//Linear probing

	float ocupacion = static_cast<float>(contador) / table.Largo;

	if (ocupacion > 0.7) // re-hashing
	{
		Array<Tupla<K, V, estado>> nueva(static_cast<nat>(table.Largo*1.7));
		Array<Tupla<K, V, estado>>::Copiar(table, nueva, 0);
		table = nueva;
	}

	const nat pos = buscar_posicion_insertar(c);
	Tupla<K, V, estado> t(c, v, OCUPADA);

	table[pos] = t;
	contador++;
}

template <class K, class V>
void HashCerradoImpl<K, V>::Borrar(const K& c)
{
	assert(EstaDefinida(c));

	nat pos = func->CodigoDeHash(c);
	while (comp.SonDistintos(c,table[pos].Dato1))
	{
		pos = pos++;

		// Con esto me aseguro de hacerlo circular
		pos = pos % table.Largo;
	}

	table[pos].AsignarDato3(BAJA);
	contador--;
}

template <class K, class V>
void HashCerradoImpl<K, V>::BorrarTodos()
{
	for (nat p = 0 ; p < table.Largo;p++) table[p].AsignarDato3(LIBRE);
	contador = 0;
}

template <class K, class V>
bool HashCerradoImpl<K, V>::EstaVacia() const
{
	return contador == 0;
}

template <class K, class V>
bool HashCerradoImpl<K, V>::EstaLlena() const
{
	return contador > table.Largo * 0.7;
}

template <class K, class V>
bool HashCerradoImpl<K, V>::EstaDefinida(const K& c) const
{
	nat pos = func->CodigoDeHash(c);
	nat iter = 0;


	while (table[pos].Dato3 != LIBRE && iter <= contador && comp.SonDistintos(c,table[pos].Dato1))
	{
		iter++;
		pos = pos++;		
		pos = pos % table.Largo;
	}

	return table[pos].Dato3 == OCUPADA;
}

template <class K, class V>
const V& HashCerradoImpl<K, V>::Obtener(const K& c) const
{
	nat pos = func->CodigoDeHash(c);
	nat iter = 0;

	while (table[pos].Dato3 == LIBRE && iter <= contador)
	{
		iter++;
		pos = pos++;
		pos = pos % table.Largo;
	}

	return table[pos].Dato2;
}

template <class K, class V>
nat HashCerradoImpl<K, V>::Largo() const
{
	return contador;
}

template <class K, class V>
Puntero<Tabla<K, V>> HashCerradoImpl<K, V>::Clonar() const
{
	return nullptr;
}

template <class K, class V>
Iterador<Tupla<K, V>> HashCerradoImpl<K, V>::ObtenerIterador() const
{
	return new HashCerradoIteracion<K, V>(*this);
}

template <class K, class V>
Puntero<ListaOrd<nat>> HashCerradoImpl<K, V>::celdas_ocupadas() const
{
	Puntero<ListaOrd<nat>> celdasOcupadas = new ListaEncadenadaImp<nat>(Comparador<nat>::Default);

	for (nat i = 0; i < table.Largo; i++)
	{
		if (table[i].Dato3 == OCUPADA)
			celdasOcupadas->InsertarOrdenado(i);
	}
	return celdasOcupadas;
}

template <class K, class V>
const Tupla<K, V>& HashCerradoImpl<K, V>::get(nat pos) const
{
	 
	return *(new Tupla<K, V>(table[pos].Dato1, table[pos].Dato2));
}


#endif
