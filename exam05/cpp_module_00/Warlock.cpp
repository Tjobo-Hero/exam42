
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