#include "CadenaHash.h"

nat CadenaHash::CodigoDeHash(const Cadena& c) const
{
	nat hashCode = 0;
	for (nat i = 0; i < c.Largo; i++)
		hashCode += static_cast<int>(c[i])*(i + 1 );
	return hashCode;
}
