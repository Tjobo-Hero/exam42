
#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <iostream>
#include <string>
#include <vector>
#include "ASpell.hpp"
#include "ATarget.hpp"

class ASpell;
class ATarget;

class Warlock
{
	private:

		std::string	_name;
		std::string _title;

		std::vector<ASpell*> _spells;

		Warlock(void);
		Warlock&		operator=(const Warlock &obj);
		Warlock(const Warlock &src);

	public:
		Warlock(const std::string &name, const std::string &title);
		~Warlock(void);
		const std::string&	getName(void) const;
		const std::string&	getTitle(void) const;
		void				setTitle(const std::string &title);
		void				introduce(void) const;

		void				learnSpell(const ASpell* spell);
		void				forgetSpell(const std::string spell_name);
		void				launchSpell(const std::string spell_name, const ATarget &target);

};
#endif