
#include "Warlock.hpp"

Warlock::Warlock(const std::string &name, const std::string &title) : _name(name), _title(title)
{
	std::cout << name << ": This looks like another boring day." << std::endl;
	return;
}

Warlock::~Warlock(void)
{
	std::cout << this->_name << ": My job here is done!" << std::endl;
	return;
}

const std::string&	Warlock::getName(void) const
{
	return this->_name;
}
const std::string&	Warlock::getTitle(void) const
{
	return this->_title;
}
void				Warlock::setTitle(const std::string &title)
{
	this->_title = title;
	return;
}
void				Warlock::introduce(void) const
{
	std::cout << this->_name << ": I am " << this->_name << ", " << this->_title << "!" << std::endl;
	return;
}
void				Warlock::learnSpell(const ASpell* spell)
{
	std::vector<ASpell*>::iterator it = _spells.begin();

	for (; it != _spells.end(); it++)
		if ((*it)->getName() == spell->getName())
			return;
	_spells.push_back(spell->clone());
}
void				Warlock::forgetSpell(const std::string spell_name)
{
	std::vector<ASpell*>::iterator it = _spells.begin();

	for (; it != _spells.end(); it++)
		if ((*it)->getName() == spell_name)
		{
			delete (*it);
			_spells.erase(it);
			return;
		}
}
void				Warlock::launchSpell(const std::string spell_name, const ATarget &target)
{
	std::vector<ASpell*>::iterator it = _spells.begin();

	for (; it != _spells.end(); it++)
		if ((*it)->getName() == spell_name)
			(*it)->launch(target);
}