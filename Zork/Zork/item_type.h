#pragma once

namespace Zork
{
    enum ItemType
    {
        ARMOR,
        WEAPON,
        RUNE,
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
        
            default:
            {
                return "NONE";
            }
        }
    }
}