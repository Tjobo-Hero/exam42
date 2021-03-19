
#include "ASpell.hpp"

ASpell::ASpell(void)
{
	return;
}

ASpell::ASpell(const std::string &name, const std::string &effects) : _name(name), _effects(effects)
{
	return;
}

ASpell::~ASpell(void)
{
	return;
}

ASpell::ASpell(const ASpell &src)
{
	*this = src;
	return;
}

ASpell&			ASpell::operator=(const ASpell &obj) 
{
	if (this != &obj)
	{
		this->_name = obj._name;
		this->_effects = obj._effects;
	}
	return *this;
}

const std::string	ASpell::getName(void) const
{
	return this->_name;
}
const std::string	ASpell::getEffects(void) const
{
	return this->_effects;
}

void				ASpell::launch(const ATarget &target) const
{
	target.getHitBySpell(*this);
	return;
}