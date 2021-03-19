#ifndef ATARGET_HPP
# define ATARGET_HPP

#include <iostream>
#include <string>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
	protected:

		std::string	_type;

	public:
		ATarget(void);
		ATarget&		operator=(const ATarget &obj);
		ATarget(const ATarget &src);
		ATarget(const std::string &type);
		virtual ~ATarget(void);

		const std::string	getType(void) const;
	
		virtual	ATarget*		clone(void) const = 0;
		void 				getHitBySpell(const ASpell &spell) const;


};
#endif