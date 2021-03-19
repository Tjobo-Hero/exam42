#ifndef DUMMY_HPP
# define DUMMY_HPP

#include <iostream>
#include <string>

#include "ATarget.hpp"

class ATarget;

class Dummy : public ATarget
{
	public:

		Dummy(void);
		~Dummy(void);

		virtual ATarget*		clone(void)  const;
};
#endif