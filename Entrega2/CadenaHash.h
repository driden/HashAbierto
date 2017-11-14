#pragma once

#include "Cadena.h"
#include "FuncionHash.h"

class CadenaHash : public FuncionHash<Cadena>
{
public:
	nat CodigoDeHash(const Cadena& c) const override;
};
