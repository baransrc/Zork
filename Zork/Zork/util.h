#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>

namespace Util
{
	inline std::vector<std::string> SplitStringToWords(std::string input)
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

	inline const bool Equals(const std::string cppString, const char* cString, const bool caseSensitive)
	{
		if (cppString.size() != strlen(cString))
		{
			return false;
		}

		if (caseSensitive)
		{
			return (cppString.compare(cString) == 0);
		}

		std::string str1 = cppString.substr(0);
		std::string str2(cString);

		std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
		std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

		return (str1.compare(str2) == 0);
	}

	inline const bool Equals(const std::string cppString1, std::string cppString2, const bool caseSensitive)
	{
		if (cppString1.size() != cppString2.size())
		{
			return false;
		}

		if (caseSensitive)
		{
			return (cppString1.compare(cppString2) == 0);
		}

		std::string str1 = cppString1.substr(0);
		std::string str2 = cppString2.substr(0);

		std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
		std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

		return (str1.compare(str2) == 0);
	}

	inline const bool Equals(const char* cString1, const char* cString2, const bool caseSensitive)
	{
		if (strlen(cString1) != strlen(cString2))
		{
			return false;
		}

		std::string str1(cString1);

		if (caseSensitive)
		{
			return (str1.compare(cString2) == 0);
		}

		std::string str2(cString2);

		std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
		std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

		return (str1.compare(str2) == 0);
	}

	inline const int RandomNumber(const int inclusiveLowerBound, const int inclusiveUpperBound)
	{
		std::random_device randomDevice; // Get a pseudorandom number from hardware
		std::mt19937 generator(randomDevice()); // Feed it as a seed to generator
		std::uniform_int_distribution<> distribution(inclusiveLowerBound, inclusiveUpperBound); // Define uniform range

		// Generate number between range:
		return distribution(generator);
	}
}