#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "entity.h"

class Entity;
class Player;

namespace Zork
{
	class World
	{
	public:

		World();
		
		bool Update(std::vector<std::string>& arguments);
		bool Parse(std::vector<std::string>& arguments);
		void GameLoop();

		~World();

	private:

		std::string DetermineCharacterName();
		void Intro();
	
	private:
		clock_t updateTimer;
		std::vector<Entity*> entities;
		Player* player;

	};
}

