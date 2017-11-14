#pragma once

#include "Puntero.h"

template <class T>
class Nodo
{
public:
	T data;
	Puntero<Nodo<T>> sig;

	Nodo(const T &data, Puntero<T> sig)
	{
		this->data = data;
		this->sig = sig;
	}

	Nodo(const T &data)
	{
		this->data = data;
		this->sig = nullptr;
	}

	~Nodo() {}
};
