
#ifndef SISTEMA_CPP
#define SISTEMA_CPP
#include "Sistema.h"
#include "CadenaHash.h"

// PRE:
// POS: ordena el array arr de menor a mayor usando el comparador comp
template <class T>
void MergeSort(Array<T> &arr, int low, int high, Comparador<T> comp)
{
	if (low >= high)
		return;
	else {
		int mid = (low + high) / 2;
		MergeSort(arr, low, mid, comp);
		MergeSort(arr, mid + 1, high, comp);
		Merge(arr, low, mid, mid + 1, high, comp);
	}
}

template <class T>
void Merge(Array<T> &arr, int left_low, int left_high, int right_low, int right_high, Comparador<T> comp)
{
	int length = right_high - left_low + 1;
	Array<T> temp(length);
	int left = left_low;
	int right = right_low;

	for (int i = 0; i < length; ++i) {

		if (left > left_high)
			temp[i] = arr[right++];

		else if (right > right_high)
			temp[i] = arr[left++];

		else if (comp.EsMenor(arr[left], arr[right]) || comp.SonIguales(arr[left], arr[right]))
			temp[i] = arr[left++];

		else
			temp[i] = arr[right++];
	}

	for (int i = 0; i < length; ++i)
		arr[left_low++] = temp[i];
}

// pre: -
// pos: devuelve una nueva cadena, que tiene los caracteres de c ordenados alfabeticamente
Cadena OrdenarCadena(Cadena c)
{
	Array<char> letras(c.Largo);
	for (nat i = 0; i < letras.Largo; i++)
		letras[i] = c[i];
	Comparador<char> comp = Comparador<char>::Default;
	MergeSort(letras, 0, letras.Largo - 1, comp);

	string palabra = "";
	for (nat i = 0; i < letras.Largo; i++)
		palabra += letras[i];


	return Cadena(palabra.c_str());
}

// pre: -
// pos: devuelve true sii cadena tiene caracteres especiales
bool TieneCaracteresEspeciales(const Cadena &cadena)
{
	int min = 97; // a
	int max = 122; // z

	bool hasSpecialChars = false;

	for (nat x = 0; x < cadena.Largo; x++)
	{
		int asciiValue = (int)cadena[x];

		if (asciiValue < min || asciiValue > max)
		{
			hasSpecialChars = true;
			break;
		}
	}

	return hasSpecialChars;
}

Sistema::Sistema(const Cadena& nombreArchivoDiccionario)
{
	// Inicialización de estructuras necesrias para resolver el problema.
	hash = new HashAbiertoImpl<Cadena, Cadena>(new CadenaHash(), 85000, Comparador<Cadena>::Default);

	// Vueltas para manejar que el input sea una Cadena
	string nombre = "";
	for (nat i = 0; i < nombreArchivoDiccionario.Largo; i++)
		nombre += nombreArchivoDiccionario[i];

	//leer el archivo y llenar el hash
	string line;
	ifstream miarchivo(nombre);
	Comparador<Cadena> comp = Comparador<Cadena>::Default;
	if (miarchivo.is_open()) {

		while (getline(miarchivo, line)) {

			std::transform(line.begin(), line.end(), line.begin(), ::tolower);

			Cadena original(line.c_str());

			if (TieneCaracteresEspeciales(original))
				continue;
			Cadena ordenada = OrdenarCadena(original);

			if (hash->EstaDefinida(ordenada))
			{
				Iterador<Tupla<Cadena, Cadena>> iter = hash->ObtenerIterador(ordenada);
				bool doble = false;
				while (iter.HayElemento()) {
					// Pära que no se duplique
					if (comp.SonIguales(iter.ElementoActual().Dato2, original))
					{						
						doble = true; 
						break;												
					}

					iter.Avanzar();
				}
				if (!doble) hash->Agregar(ordenada, original);
			}else
			{
				hash->Agregar(ordenada, original);
			}			
		}

		miarchivo.close();
	}
}

Sistema::~Sistema()
{
}

// Pre
// pos: se devuelve una nueva instancia de Cadena con todos los caracteres de c en lowercase
Cadena ToLower(const Cadena &c)
{
	const int asciiSuma = 32;
	int asciiValue;

	string lower = "";

	for (nat i = 0; i < c.Largo; i++)
	{
		asciiValue = static_cast<int>(c[i]);
		if (!(asciiValue < 65 || asciiValue > 90))
			asciiValue = asciiValue + asciiSuma;

		lower += static_cast<char>(asciiValue);
	}

	return Cadena(lower.c_str());
}

// Ejercicio 1: Anagramas
Array<Cadena> Sistema::Anagramas(const Cadena& c)
{
	Cadena minuscula = ToLower(c);
	Cadena ordenada = OrdenarCadena(minuscula);
	Comparador<Cadena> comp = Comparador<Cadena>::Default;

	Iterador<Tupla<Cadena, Cadena>> iter = hash->ObtenerIterador();

	Puntero<ListaOrd<Cadena>> lista = new ListaEncadenadaImp<Cadena>(comp);

	while (iter.HayElemento()) {
		if (comp.SonIguales(iter.ElementoActual().Dato1, ordenada))
			//if (!comp.SonIguales(iter.ElementoActual().Dato2, minuscula))
			lista->InsertarOrdenado(iter.ElementoActual().Dato2);
		iter.Avanzar();
	}

	this->anagramas = (lista->Largo());
	for (nat n = 0; n < anagramas.Largo; n++)
		anagramas[n] = lista->Obtener(n);

	return anagramas;
}


#endif