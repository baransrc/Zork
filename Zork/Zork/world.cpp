#include "world.h"

Zork::World::World()
{
	std::cout << "Initialized World!" << std::endl;
}

bool Zork::World::Update(std::vector<std::string>& arguments)
{
	return false;
}

bool Zork::World::Parse(std::vector<std::string>& arguments)
{
	return false;
}

void Zork::World::GameLoop()
{
	// TODO: Implement.
}

Zork::World::~World()
{
	// TODO: Implement.
}
