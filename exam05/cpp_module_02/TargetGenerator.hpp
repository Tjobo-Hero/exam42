#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include "ATarget.hpp"

class ATarget;

class TargetGenerator
{
	private:

		std::vector<ATarget*> _targets;

		TargetGenerator&		operator=(const TargetGenerator &obj);
		TargetGenerator(const TargetGenerator &src);

	public:
		TargetGenerator(void);
		~TargetGenerator(void);
		
		void				learnTargetType(ATarget* target);
		void				forgetTargetType(const std::string type);
		ATarget*			createTarget(const std::string type);

};
#endif