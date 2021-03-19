#ifndef ASPELL_HPP
# define ASPELL_HPP

#include <iostream>
#include <string>
#include "ATarget.hpp"

class ATarget;

class ASpell
{
	protected:

		std::string	_name;
		std::string _effects;


	public:
		ASpell(void);
		ASpell&		operator=(const ASpell &obj);
		ASpell(const ASpell &src);
		ASpell(const std::string &name, const std::string &effects);
		virtual ~ASpell(void);

		const std::string	getName(void) const;
		const std::string	getEffects(void) const;
		virtual	ASpell*		clone(void) const = 0;
		void				launch(const ATarget &target) const;


};
#endif