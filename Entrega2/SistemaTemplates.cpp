#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"
#include "HashAbiertoImpl.h"
#include "HashCerradoImpl.h"

template <class C, class V>
Puntero<Tabla<C, V>> Sistema::CrearTablaHashAbierto(nat cubetas, Puntero<FuncionHash<C>> fHash, const Comparador<C>& comp)
{
	Puntero<Tabla<C, V>> pTabla = new HashAbiertoImpl<C, V>(fHash, cubetas, comp);
	return pTabla;
}

template <class C, class V>
Puntero<Tabla<C, V>> Sistema::CrearTablaHashCerrado(nat cubetas, Puntero<FuncionHash<C>> fHash, const Comparador<C>& comp)
{
	Puntero<Tabla<C, V>> pTabla = new HashCerradoImpl<C, V>(cubetas, fHash, comp);
	return pTabla;
}

//Pre: raiz es un arbol (binario)
//Pos: devuelve true sii todos los nodos del arbol son menores al d
template <class T>
bool SonMenores(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp, const T& d) {

	if (raiz != nullptr)
	{
		if (comp.EsMayor(d, raiz->dato))
		{
			return SonMenores(raiz->izq, comp, d) && SonMenores(raiz->der, comp, d);
		}
		return false;
	}
	return true;

}


//Pre: raiz es un arbol (binario)
//Pos: devuelve true sii todos los nodos del arbol son mayores al d
template <class T>
bool SonMayores(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp, const T& d) {

	if (raiz != nullptr)
	{
		if (comp.EsMenor(d, raiz->dato))
		{
			return SonMayores(raiz->izq, comp, d) && SonMayores(raiz->der, comp, d);
		}
		return false;
	}
	return true;

}

// PRE: raiz es un arbol binario
// POS: Devuelve true sii es un ABB
template <class T>
bool EsABB(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp)
{
	if (raiz == nullptr)
		return true;

	bool valeDer = true;
	bool valeIzq = true;	
	
	if (raiz->izq != nullptr) {
		valeIzq = SonMenores(raiz->izq, comp, raiz->dato);
	}
	if (raiz->der != nullptr) {
		valeDer = SonMayores(raiz->der, comp, raiz->dato);
	}
	return valeIzq && valeDer;
}

// PRE: raiz es un arbol binario
// POS: Devuelve la altura de la raiz
template <class T>
int AlturaArbol(Puntero<NodoArbol<T>> raiz)
{
	if (raiz == nullptr) return -1;
	int hIzq, hDer;

	hDer = AlturaArbol(raiz->der);
	hIzq = AlturaArbol(raiz->izq);

	if (hDer > hIzq)
		return 1 + hDer;

	return 1 + hIzq;

}
// PRE: raiz es un arbol binario
// POS: Devuelve true sii esta balanceado
template <class T>
bool IsAVL(Puntero<NodoArbol<T>> raiz)
{
	if (raiz == nullptr) {
		return true;
	}
	int balance = AlturaArbol(raiz->izq) - AlturaArbol(raiz->der);

	balance = balance * balance;
	if (balance == 0 || balance == 1)
		return IsAVL(raiz->izq) && IsAVL(raiz->der);
	else
		return false;
}

// PRE: raiz es un arbol binario
// POS: Devuelve true sii es un AVL
template <class T>
bool Sistema::EsAVL(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp)
{
	return EsABB(raiz, comp) && IsAVL(raiz);
}



#endif