#include "CasoDePrueba.h"
#include "PruebaMemoria.h"
#include "ConductorPrueba.h"
#include "Sistema.h"

#include <string>
#include <cctype>

Puntero<Sistema> pSist = nullptr;
Puntero<Sistema> Inicializar()
{
	if (pSist == nullptr)
		pSist = new Sistema("diccionario.txt");
	return pSist;
}

void main()
{
	Puntero<ConductorPrueba> cp = new ConductorPrueba();
	Array<Puntero<Prueba>> pruebas = Array<Puntero<Prueba>>(3);
	pruebas[0] = new PruebaMemoria();
	pruebas[1] = new CasoDePrueba(Inicializar);
	pruebas[2] = pruebas[0];
	cp->CorrerPruebas(pruebas.ObtenerIterador());

	system("pause");
}

