#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <time.h>

namespace Zork
{
	class Entity;
	class Player;


	class World
	{
	public:

		World();
		
		void Update(std::vector<std::string>& arguments);
		bool Parse(std::vector<std::string>& arguments);
		void GameLoop();

		~World();

	public:
		std::list<Entity*> entities;

	private:
		std::string DetermineCharacterName();
		void Intro();
	
	private:
		clock_t updateTimer;
		
		Player* player;
	};
}

