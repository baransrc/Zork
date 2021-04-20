#include "util.h"

std::vector<std::string> Util::SplitStringToWords(std::string input)
{
	std::vector<std::string> container;
	std::istringstream inputStream(input);

	for (std::string str; inputStream >> str; )
	{
		if (str.length() <= 0)
		{
			continue;
		}
		
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

int Util::RandomNumber(const int inclusiveLowerBound, const int inclusiveUpperBound)
{
	std::random_device randomDevice; // Get a pseudorandom number from hardware
	std::mt19937 generator(randomDevice()); // Feed it as a seed to generator
	std::uniform_int_distribution<> distribution(inclusiveLowerBound, inclusiveUpperBound); // Define uniform range

	// Generate number between range:
	return distribution(generator); 
}