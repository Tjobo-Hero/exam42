#include "ATarget.hpp"

ATarget::ATarget(void)
{
	return;
}

ATarget::ATarget(const std::string &type) : _type(type)
{
	return;
}

ATarget::~ATarget(void)
{
	return;
}

ATarget::ATarget(const ATarget &src)
{
	*this = src;
	return;
}

ATarget&			ATarget::operator=(const ATarget &obj) 
{
	if (this != &obj)
	{
		this->_type = obj._type;
	}
	return *this;
}

const std::string	ATarget::getType(void) const
{
	return this->_type;
}


void 				ATarget::getHitBySpell(const ASpell &spell) const
{
	std::cout << this->_type << " has been " << spell.getEffects() << "!" << std::endl;
	return;
}