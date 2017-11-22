#ifndef SISTEMA_H
#define SISTEMA_H

#include <fstream>
#include <string>
#include <algorithm>

#include "Cadena.h"
#include "Puntero.h"
#include "Tupla.h"
#include "NodoArbol.h"
#include "Tabla.h"
#include "FuncionHash.h"
#include "HashAbiertoImpl.h"


class Sistema
{
private:
	Puntero<HashAbiertoImpl<Cadena, Cadena>> hash;
	Array<Cadena> anagramas;
	
public:
	Sistema(const Cadena& nombreArchivoDiccionario);
	~Sistema();

	// Ejercicio 1: Anagramas, TablaHash abierta y cerrada
	Array<Cadena> Anagramas(const Cadena& c);
	
	template <class C, class V>
	Puntero<Tabla<C, V>> CrearTablaHashAbierto(nat cubetas, Puntero<FuncionHash<C>> fHash, const Comparador<C>& comp);
	
	template <class C, class V>
	Puntero<Tabla<C, V>> CrearTablaHashCerrado(nat cubetas, Puntero<FuncionHash<C>> fHash, const Comparador<C>& comp);

	// Ejercicio 2: AVL
	template <class T>
	bool EsAVL(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp);

private:
	//Atributos necesarios para cumplir con las operaciones.

};


#include "SistemaTemplates.cpp"

#endif
