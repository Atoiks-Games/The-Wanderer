/**
  * main.cxx -- The entry point of the application
  *
  * Copyright (C) 2016 Atoiks Games Group
  *
  * The Wanderer is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your opinion) any later version.
  *
  * The Wanderer is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

#include "Page.hxx"
#include "Read.hxx"
#include "Items.hxx"
#include "Party.hxx"
#include "Utils.hxx"
#include "Events.hxx"
#include "Player.hxx"
#include "Chapter.hxx"
#include "Enemies.hxx"
#include "Players.hxx"

#include <map>
#include <memory>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace utils;
using namespace wanderer;

int
main (void)
{
	Chapter prologue("\n\n\t_PROLOGUE_\n\n", {
		Page([](Party &_p){
			std::cout <<
"The Wanderer\nCopyright (C) 2016 Atoiks Games Group\n"
"License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>"
"\nThis is free software, and you are welcome to redistribute it under certain"
"\nconditions. This program comes with ABSOLUTELY NO WARRANTY.\n" <<
std::endl;
			return true;
		}),
		Page([](Party &party){
			std::cout << "Give me your name" << std::endl;
			std::string name = io::read_non_empty_line();
			party[name] = mem::unique_to_shared(read::race());
			std::cout << name << ": " << party[name]->default_greeter() <<
"\nAlright " << name <<
"! Give me three other names for your fellow party members" << std::endl;
			for (int i = 0; i < 3; ++i)
			{
				name = read::new_name(party, std::to_string(i + 1) + ">> ");
				party[name] = mem::unique_to_shared(read::race());
				std::cout << name << ": " << party[name]->default_greeter()
						<< std::endl;
			}

			std::cout << '\n';
			for (auto it = party.begin(); it != party.end(); ++it)
			{
				std::cout << "Player: " << it->first <<
'(' << it->second->class_name() << ")\n" <<
it->second->get_stats() << '\n' << std::endl;
			}
			return true;
		}),
		Page([](Party &party){
			std::cout <<
"Your party wakes up in their rooms of the inn. It's morning. They can hear\n"
"the birds chirping and the nearby river flowing. They get out of bed and\n"
"look around the tiny room they slept in.\n"
"As they begin to get dressed they remeber that their adventuring contractor\n"
"said he would be sending them a new task today. It would be in a parcel at\n"
"the end of the long and twisted road to the dropzone." << std::endl;
			do
			{
				std::cout <<
"\nWhat should your party do?\n\n"
"-i Inspect Their Rooms\n"
"-m Meet up in The Tavern Below Their Rooms" << std::endl;
				std::string choice = io::read_non_empty_line();

				if (choice == "m" || choice == "M") break;
				if (choice == "i" || choice == "I")
				{
					std::cout <<
"Their rooms are small and dusty. Each character's adventuring pack lays on\n"
"the small bed. The window is opaque with dust and grime. It isn't pretty,\n"
"but it's cheap." << std::endl;
				}
				else std::cout << "What is that?";
			}
			while (true);
			return events::send_player_to_parcel(party);
		}),
	});

	prologue.and_then(std::shared_ptr<Chapter>(
		new Chapter("\n\n\t_CHAPTER 1: The Missing Merchant_\n\n", {
			Page([](Party &p){
				std::cout <<
"Its been a month of travelling for your group. The contractor has sent the\n"
"party to find the missing merchant with of name of Lasrof Icip. You arrive\n"
"at the mouth of the cave where he is last seen. The snow storm has picked up\n"
"up its intensity";
				do
				{
					std::cout <<
"\nDo you go inside?\n\n-i go inside\n-o stay outside\n-a look around" <<
std::endl;
					const std::string opt = io::read_non_empty_line();
					if (opt == "a")
					{
						std::cout <<
"You notice the cave mouth is about to collapse! You tread carefully into the\n"
"cave and the entrance collapses behind you!" << std::endl;
						return true;
					}
					if (opt == "o")
					{
						std::cout <<
"\n\n\t...Couple thousand years later...\n"
"\tNEWS HEADLINE: RESEARCHERS FIND ANCIENT ADVENTURERS FROZEN IN THE SNOW!\n\n"
"(Your party members are the 'ancient adventurers' in case you didn't realize)"
<< std::endl;
						return false;
					}
					if (opt == "i")
					{
						std::cout <<
"As you enter the cave, the cave collpases" << std::endl;
						Party tmp;
						for (auto it = p.begin(); it != p.end(); ++it)
						{
							if (it->second->roll_dexterity() > 12)
							{
								std::cout << it->first <<
" makes it into the cave" << std::endl;
								tmp[it->first] = it->second;
							}
							else
							{
								std::cout << it->first <<
" gets crushed and dies a quick painful death" << std::endl;
							}
						}
						if (tmp.empty())
						{
							std::cout <<
"All your party members died!" << std::endl;
							return false;
						}
						p = tmp;
						return true;
					}
					std::cout << "What is that?" << std::endl;
				}
				while (true);
				return true;
			}),
			Page([](Party &p){
				std::cout <<
"You make your way in. The cave is cold and damp, the tunnel beckons you deeper"
"\ninto the cave. Besides the door there is a small chest." << std::endl;
				std::string mimic_senser = "";
				for (auto it = p.begin(); it != p.end(); ++it)
				{
					if (it->second->roll_wisdom() > 6)
					{
						mimic_senser = it->first;
						break;
					}
				}

				do
				{
					std::cout <<
"Here are your choices\n\n-d Go deeper\n-i Inspect room\n-c Open chest" <<
std::endl;
					const std::string opt = io::read_non_empty_line();
					if (opt == "d")
					{
						std::cout <<
"You head deeper into the cave..." << std::endl;
						return true;
					}
					if (opt == "i")
					{
						std::cout <<
"It's a cave (with a tunnel and a small chest that is behind a door)" <<
std::endl;
						if (!mimic_senser.empty())
						{
							std::cout <<
mimic_senser << ": I am pretty sure the chest has teeth!" << std::endl;
						}

						continue;
					}
					if (opt == "c")
					{
						const std::string name = read::name_of_player(p,
							   "Which of your adventurers runs the fastest to"
							   " the chest?");
						auto player = p.find_player(name);
						if (player->roll_wisdom() > 19)
						{
							std::cout << name <<
" uses a stick to knock out one piece of gold" << std::endl;
							player->inventory.deposit(1);
						}
						else
						{
							std::cout << name <<
" died. The chest smiles at you. It appears to be a mimic.\n"
"(It is possible to get gold though...)" << std::endl;
							p.remove_player(name);
							if (p.empty())
							{
								std::cout <<
"All your group members are dead!\n";
								return false;
							}
						}
						continue;
					}
					std::cout << "What is that?" << std::endl;
				}
				while (true);
				return true;
			}),
			Page([](Party &p){
				std::cout <<
"You go a bit further in the cave and find two skeletons conversing" <<
std::endl;
				bool has_attacked = false;
				do
				{
					std::cout << "What do you do?\n\n-a Send someone to attack";
					if (!has_attacked)
					{
						std::cout <<
"\n-s Attempt to sneak past\n-c Listen to their conversation";
					}
					std::cout << "\n-t Send someone to talk" << std::endl;
					const std::string opt = io::read_non_empty_line();
					if (opt == "a")
					{
						has_attacked = true;
						auto ret = events::fight_skeleton(p,
								read::name_of_players(p,
									"Who will intervene the situation?"));
						if (ret)
						{
							p.begin()->second->inventory.add_item(
									std::shared_ptr<Item>(new items::Key()));
							std::cout << p.begin()->first <<
" got a key from finishing up the skeleton guards and looting them." <<
std::endl;
							return true;
						}
						if (p.empty()) return false;
						continue;
					}
					if (opt == "s" && !has_attacked)
					{
						for (auto it = p.begin(); it != p.end(); )
						{
							if (it->second->roll_dexterity() > 6)
							{
								std::cout <<
it->first << " went undetected!" << std::endl;
								++it;
							}
							else
							{
								if (events::fight_skeleton(p, {it->first}))
								{
									// That means there are no more skeletons
									// meaning all remaining players make it
									std::cout <<
"The remaining players make it without sneaking" << std::endl;
									return true;
								}
								++it;
							}
						}
						return !p.empty();
					}
					if (opt == "c" && !has_attacked)
					{
						std::string infernal_player = "";
						for (auto it = p.begin(); it != p.end(); ++it)
						{
							if (dynamic_cast<players::Infernal*>(
										it->second.get()) != nullptr)
							{
								infernal_player = it->first;
								break;
							}
						}

						if (infernal_player.empty())
						{
							std::cout <<
"You have no clue what they are saying..." << std::endl;
						}
						else
						{
							std::cout << infernal_player <<
": They are talking about life, this group called Atoiks Games, wolves,\n"
"zombies, cats, ... (Basically random junk that is not related to the chapter)"
<< std::endl;
						}
						continue;
					}
					if (opt == "t")
					{
						auto name = read::name_of_player(p,
								"Who's breaking the ice?");
						auto player = p.find_player(name);
						int dc_charisma = 18;
						if (dynamic_cast<players::Infernal*>(player.get())
								!= nullptr)
						{
							dc_charisma = 2;
						}
						if (player->roll_charisma() > dc_charisma)
						{
							std::cout <<
"You have befriended the skeletons. They join your party!\n"
"Give me two names (for the skeleton friends)" << std::endl;
							for (std::size_t i = 0; i < 2; ++i)
							{
								auto name = read::new_name(p,
										std::to_string(i + 1) + ">> ");
								p[name] = std::shared_ptr<Player>(
										new enemies::Skeleton());
								std::cout <<
name << ": " << p[name]->default_greeter() << std::endl;
							}
							return true;
						}
						else
						{
							p.remove_player(name);
							std::cout <<
"The skeletons murder " << name << ".\n"
"Guess they don't like bad puns." << std::endl;
							continue;
						}
					}
					std::cout << "What is that?" << std::endl;
				}
				while (true);
				return true;
			}),
			Page([](Party &p){
				std::cout <<
"You continue deeper into the dungeon" << std::endl;
				return true;
			})
		})
	));

	Party party;
	prologue(party);

	std::cout << "\n\n\tGG (Hit enter to quit)" << std::endl;
	std::string t;
	std::getline(std::cin, t);
	return 0;
}
