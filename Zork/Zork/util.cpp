#include "util.h"

std::vector<std::string> Util::splitStringToWords(std::string input)
{
	std::vector<std::string> container;
	std::istringstream inputStream(input);

	for (std::string str; inputStream >> str; )
	{
		container.push_back(str);
	}

	return container;
}

bool Util::Equals(const std::string cppString, const char* cString)
{
	return (cppString.compare(cString) == 0);
}

bool Util::Equals(const std::string cppString1, std::string cppString2)
{
	return (cppString1.compare(cppString2) == 0);
}

bool Util::Equals(const char* cString1, const char* cString2)
{
	std::string first = cString1;

	return (first.compare(cString2) == 0);
}