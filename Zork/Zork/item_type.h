#pragma once

namespace Zork
{
    enum ItemType
    {
        ARMOR,
        WEAPON,
        RUNE,
		CONTAINER,
    };

    inline const char* ItemTypeToString(const ItemType type)
    {
        switch (type)
        {
            case ItemType::ARMOR:
            {
                return "Armor";
            }
            
            case ItemType::WEAPON:
            {
                return "Weapon";
            }

            case ItemType::RUNE:
            {
                return "Rune";
            }

			case ItemType::CONTAINER:
			{
				return "Container";
			}
        
            default:
            {
                return "NONE";
            }
        }
    }
}