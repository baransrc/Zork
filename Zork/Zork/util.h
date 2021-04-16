#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace Util
{
	std::vector<std::string> splitStringToWords(std::string input)
	{	
		std::vector<std::string> container;
		std::istringstream inputStream(input);
		
		for (std::string str; inputStream >> str; )
		{
			container.push_back(str);
		}

		return container;
	}
}