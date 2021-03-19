#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

#include <iostream>
#include <string>
#include <vector>
#include "ASpell.hpp"

class ASpell;

class SpellBook
{
	private:

		std::vector<ASpell*> _spells;

		SpellBook&		operator=(const SpellBook &obj);
		SpellBook(const SpellBook &src);

	public:
		SpellBook(void);
		~SpellBook(void);
		
		void				learnSpell(ASpell* spell);
		void				forgetSpell(const std::string spell_name);
		ASpell*				createSpell(const std::string spell_name);

};
#endif