#include <iostream>
#include <string>
#include "util.h"
#include "world.h"

int main()
{
	// Initialize World:
	Zork::World world;
	std::string playerName = world.GetPlayerName();

	// While game is not ended, take input and update the game:
	while (!world.IsGameEnded())
	{
		std::string userInput = "";

		getline(std::cin, userInput);
		
		std::vector<std::string> tokens = Util::SplitStringToWords(userInput);

		world.Update(tokens);

		if (!world.IsGameEnded())
		{
			std::cout << std::endl << playerName << "> ";
		}

		tokens.clear();
	}

	std::cout << std::endl << "Thank you for playing!" << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}