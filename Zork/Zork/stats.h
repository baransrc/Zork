#pragma once

namespace Zork
{
    // Stats are stored inside this struct to 
    // support any additional stat that may be
    // added to the game in the future without
    // any need to change the constructors of 
    // classes that uses stats. 
    // Such as Item and Creature.
    struct Stats 
	{
		int health;
		int attack;
		int defence;
	};   
}