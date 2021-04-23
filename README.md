# Zork
License: https://github.com/baransrc/Zork/blob/main/LICENSE <br />
Repository: https://github.com/baransrc/Zork <br />

## About Game
In this version of Zork you play a mage lost in a dungeon.<br />
In the game there is a elemental rune system. If you equip an elemental rune, it will enable player to cast spells of that element.<br />
Elemental Dominance works as follows:<br />
-  Fire is very effective against Air.<br/>
-  Air is very effective against Earth.<br/>
-  Earth is very effective against Water.<br/>
-  Water is very effective against Fire.<br/>
-  Fire is not effective on Water.<br />
-  Water is not effective on Earth.<br />
-  Earth is not effective on Air.<br />
-  Air is not effective on Fire.<br />
-  Rest is effective to eachother.<br />
So, as an example, if you do "cast water arcanum Topra" it will not deal any damage considering topra is a Creature of type Earth.<br />

In addition to spell and elements system, the game utilizes classic rpg stat system. The stats inside the game are as follows: <br />
- Attack (Increases damage)<br />
- Defence (Decreases the damage taken by other's attacks)<br />
- Health (Increases health)<br />
By killing each monster in the game, player gains one stat point to commit to one of three stats.<br />

In the game, runes are mostly acquired by killing a monster of that elemental type. In addition to the combat aspects of the runes, they also act as a key to unlock the exit of the dungeon. Game prompts user to earn all runes and place them inside the obelisk in the starting room.<br />
### Map
![Map](https://user-images.githubusercontent.com/42971567/115863520-3cce1b00-a43e-11eb-8979-3cf024245d73.png)


## How To Play
- cls/clear/flush:<br />
Clears the terminal.<br />

- drop/put/place:<br />
"drop/put/place item_0" drops item_0 to current room if item_0 is in inventory.<br />
"drop/put/place item_0 inside/in/on/.../ item_1" places item_0 inside item_1.<br />

- take/loot/get/pick:<br />
"take/loot/get/pick item_0" adds the item with name item_0 to the inventory.<br />
"take/loot/get/pick item_0 from/../ item_1" takes the item_0 from item_1 and adds it to the inventory.<br />

- go/move/walk:<br />
If follwed by north/south/east/west, makes player move to that direction if an exit exists and it's unlocked.<br />

- look/gaze/l:<br />
"look/gaze/l" shows the description of the current room.<br />
"look/gaze/l entity_0" shows description of entity_0.<br />

- cast/use/throw:<br />
"cast/use/throw prayer" increases player's health.<br />
"cast/use/throw fire/earth/water/air arcanum monster_name" deals damage to monster_name if the corresponding rune of the element is equipped. <br />
"cast/use/throw fire/earth/water/air arcanum" deals damage to previous target if the corresponding rune of the element is equipped. <br />
"cast/use/throw fire/earth/water/air stun monster_name" stuns monster_name for 0,1 or 2 turns depending on the element effectiveness. <br />
"cast/use/throw fire/earth/water/air stun" stuns previous target for 0,1 or 2 turns depending on the element effectiveness. <br />

- examine/inspect/info:<br />
"info/inspect/examine character_name/me" displays detailed info such as stats, equipped items and runes of player.<br />
"examine/inspect/info entity_0" displays description of entity_0.<br />

- equip/eq:<br />
"equip/eq item_0" makes player character equip item_0 in her inventory.<br />

- unequip/uneq:<br />
"unequip/uneq item_0" makes player character unequip the equipped item_0.<br />

- commit/add:<br />
"commit/add attack/defence/health number" will increase that certain stat by number if that amount of uncommitted points are available.<br />

- bag/inventory/inv:<br />
Lists the items in player's inventory.<br />

- exit/quit/terminate/esc:<br />
Terminates the game.<br />

## Spoilers
One can follow the following path to win the game:<br />
- go west
- info trunk
- take sendulai from trunk
- equip sendulai
- go north
- info chest
- take robe from chest
- equip robe
- go south
- go south
- go south
- take staff
- equip staff
- info me (you will see 4 uncommitted stat points)
- commit attack 2
- commit defence 2
- go east
- info topra
- cast air arcanum topra (2 - 4 times, optionally you can use "cast air stun topra" to stun it for 2 turns)
- take traiche
- equip traiche
- commit health 1
- cast prayer (do this until your health is full)
- go north
- cast air stun syon
- cast air arcanum (2 - 4 times)
- take elemyr
- equip elemyr
- commit attack 1
- cast prayer (do this until your health is full)
- go north
- cast water stun od (immediately do this, od is an angry creature and will attack you the moment you enter the room)
- cast water arcanum (2 - 4 times)
- take faerl
- equip faerl
- go south
- info obelisk
- place faerl inside obelisk
- place elemyr inside obelisk
- place traiche inside obelisk
- place sendulai inside obelisk
- go east

# Development Notes
Developing this project was more of a time challenge for me. Since it has been more than a year since I used C++ in a object oriented way, codebase may not be in it's best state possible. Aside from technical related stuff, developing a text adventure game turned out to be a lot more fun then I imagined, as it challenges your imagination to illustrate the game with words.
