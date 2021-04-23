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
		void UpdateEntities();

		const std::string GetPlayerName() const;
		const bool IsGameEnded() const;

		~World();

	public:
		std::list<Entity*> entities;

	private:
		std::string DetermineCharacterName();
		std::string Intro();
	
	private:
		Player* player;
		bool userQuit;
	};
}

