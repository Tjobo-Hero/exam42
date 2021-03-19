
#include "Polymorph.hpp"

Polymorph::Polymorph(void) : ASpell("Polymorph","turned into critter")
{
	return;
}

Polymorph::~Polymorph(void)
{
	return;
}

ASpell*		Polymorph::clone(void) const
{
	return new Polymorph(*this);
}