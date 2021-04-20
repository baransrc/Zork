#include <iostream>
#include <string>
#include "util.h"
#include "world.h"

int main()
{
	// Initialize World:
	Zork::World* world = new Zork::World();

	// Trying input management:
	while (true)
	{
		std::string userInput = "";

		getline(std::cin, userInput);
		
		std::vector<std::string> tokens = Util::SplitStringToWords(userInput);

		world->Update(tokens);

		tokens.clear();
	}

	system("pause");

	return EXIT_SUCCESS;
}