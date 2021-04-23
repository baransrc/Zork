#include <iostream>
#include <string>
#include "util.h"
#include "world.h"

int main()
{
	// Initialize World:
	Zork::World world;
	std::string playerName = world.GetPlayerName();

	// Trying input management:
	while (true)
	{
		std::string userInput = "";

		getline(std::cin, userInput);
		
		std::vector<std::string> tokens = Util::SplitStringToWords(userInput);

		world.Update(tokens);

		std::cout << std::endl << playerName << "> ";

		tokens.clear();
	}

	system("pause");

	return EXIT_SUCCESS;
}