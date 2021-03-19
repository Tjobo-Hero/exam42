

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(void)
{
	return;
}

TargetGenerator::~TargetGenerator(void)
{
	std::vector<ATarget*>::iterator it = _targets.begin();
	for (; it != _targets.end(); it++)
		delete (*it);
	return;
}

void				TargetGenerator::learnTargetType(ATarget* target)
{
	std::vector<ATarget*>::iterator it = _targets.begin();

	for (; it != _targets.end(); it++)
		if ((*it)->getType() == target->getType())
			return;
	_targets.push_back(target->clone());
}
void				TargetGenerator::forgetTargetType(const std::string type)
{
	std::vector<ATarget*>::iterator it = _targets.begin();

	for (; it != _targets.end(); it++)
		if ((*it)->getType() == type)
		{
			delete (*it);
			_targets.erase(it);
			return;
		}
}
ATarget*				TargetGenerator::createTarget(const std::string type)
{
	std::vector<ATarget*>::iterator it = _targets.begin();

	for (; it != _targets.end(); it++)
		if ((*it)->getType() == type)
			return (*it);
	return NULL;
}