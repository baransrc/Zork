#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <random>

namespace Util
{
	std::vector<std::string> SplitStringToWords(std::string input);

	bool Equals(const std::string cppString, const char* cString);

	bool Equals(const std::string cppString1, std::string cppString2);

	bool Equals(const char* cString1, const char* cString2);

	int RandomNumber(const int inclusiveLowerBound, const int inclusiveUpperBound);
}