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
#include "Party.hxx"
#include "Utils.hxx"
#include "Player.hxx"
#include "Chapter.hxx"
#include "Enemies.hxx"
#include "Players.hxx"

#include <map>
#include <memory>
#include <random>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace utils;
using namespace wanderer;

std::unique_ptr<Player>
read_player_race()
{
	std::cout <<
"Pick a race between Dwarf, Human, Elf, Gnome, Infernal and Lizardfolk"
			<< std::endl;
	do
	{
		const std::string str = io::read_non_empty_line();
		if (str::iequals("d", str) || str::iequals("dwarf", str))
		{
			return std::unique_ptr<Player>(new players::Dwarf());
		}
		if (str::iequals("h", str) || str::iequals("human", str))
		{
			return std::unique_ptr<Player>(new players::Human());
		}
		if (str::iequals("e", str) || str::iequals("elf", str))
		{
			return std::unique_ptr<Player>(new players::Elf());
		}
		if (str::iequals("g", str) || str::iequals("gnome", str))
		{
			return std::unique_ptr<Player>(new players::Gnome());
		}
		if (str::iequals("i", str) || str::iequals("infernal", str))
		{
			return std::unique_ptr<Player>(new players::Infernal());
		}
		if (str::iequals("l", str) || str::iequals("lizardfolk", str))
		{
			return std::unique_ptr<Player>(new players::Lizardfolk());
		}
		std::cout << "No race was associated with " << str << std::endl;
	}
	while (true);
}

int
main (void)
{
	Chapter prologue("\n\n\t_PROLOGUE_\n\n", {
		Page([](Party &_p){
			std::cout <<
"The Wanderer\nCopyright (C) 2016 Atoiks Games Group\n"
"License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>"
"\n\nThis is free software, and you are welcome to redistribute it"
" under certain conditions. This program comes with ABSOLUTELY NO WARRANTY.\n" <<
std::endl;
			return true;
		}),
		Page([](Party &party){
			std::cout << "Give me your name" << std::endl;
			std::string name = io::read_non_empty_line();
			party[name] = mem::unique_to_shared(read_player_race());
			std::cout << name << ": " << party[name]->default_greeter() <<
"\nAlright " << name <<
"! Give me three other names for your fellow party members" << std::endl;
			for (int i = 0; i < 3; ++i)
			{
				do
				{
					name = io::read_non_empty_line(std::to_string(i + 1) + ">> ");
					if (party.find_player(name).get() != nullptr)
					{
						std::cout <<
"There is already a party member with the name " << name << ".\nTry again"
								<< std::endl;
					}
					else break;
				}
				while (true);
				party[name] = mem::unique_to_shared(read_player_race());
				std::cout << name << ": " << party[name]->default_greeter()
						<< std::endl;
			}

			for (auto it = party.begin(); it != party.end(); ++it)
			{
				std::cout << "Player: " << it->first <<
'(' << it->second->class_name() << ")\n" <<
it->second->get_stats() << '\n' << std::endl;
			}
			return true;
		})
	});

	prologue.and_then(std::shared_ptr<Chapter>(
		new Chapter("\n\n\t_CHAPTER 1: The Missing Merchant_\n\n", {
			Page([](Party &party){
				std::cout <<
"Your party wakes up in their rooms of the inn. It's morning. They can hear "
"the birds chirping and the nearby river flowing. "
"They get out of bed and look around the tiny room they slept in.\n "
"As they begin to get dressed they remeber that their adventuring "
"contractor said he would be sending them a new task today. "
"It would be in a parcel at the end of the long and twisted road "
"to the dropzone." << std::endl;
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
"Their rooms are small and dusty. Each character's "
"adventuring pack lays on the small bed. The window is "
"opaque with dust and grime. It isn't pretty, but it's cheap." << std::endl;
					}
					else std::cout << "What is that?";
				}
				while (true);

				std::string name;
				do
				{
					std::cout <<
"Your party assembles down in the tavern. "
"They speak among themselves, trying to decide which party member "
"should go out to get the parcel.\nWho should go? Write the character's "
"full name" << std::endl;
					name = io::read_non_empty_line();
					if (party.find_player(name).get() == nullptr)
					{
						std::cout <<
"Maybe you suck at spelling, because no one is called " << name << std::endl;
					}
					else break;
				}
				while (true);
				std::cout <<
"Ok! You sent " << name << " to get the parcel" << std::endl;

				const std::size_t wolves = 2;
				std::cout << name <<
": I see wolves. Wolves everywhere (" << wolves << " of them)!" << std::endl;
				enemies::Wolf pack[wolves];
				for (std::size_t i = 0; i < wolves; ++i)
				{
					auto player = party.find_player(name);
					do
					{
						if (pack[i].attack(*player))
						{
							if (player->hitpoints < 1)
							{
								std::cout << name <<
" did not make it...\nThe remaining wolves seemed to have went away" <<
std::endl;
								party.remove_player(name);
								std::random_device rd;
								std::mt19937 gen(rd());
								std::uniform_int_distribution<> d(1, 10);
								if (d(gen) > 6)
								{
									std::cout <<
"One of your party members 'senses' the death of " << name <<
" and has decided to abort the mission!\n\nGG" << std::endl;
									return false;
								}
								return true;
							}
							else
							{
								std::cout << name << ": Ouch!" << std::endl;
							}
						}
						else
						{
							std::cout << name <<
" dodged the wolf's attack" << std::endl;
						}

						if (player->attack(pack[i]))
						{
							std::cout << name <<
" hit the wolf";
							if (pack[i].hitpoints < 1)
							{
								std::cout <<
" and it is dead!\n" << name << " has " << player->hitpoints <<
" hit points remaining\n" << std::endl;
								break;
							}
							std::cout << std::endl;
						}
						else
						{
							std::cout <<
"The wolf dodged " << name << "'s attack" << std::endl;
						}
						{
							std::cout <<
name << " has hitpoints: " << player->hitpoints <<
"\nWolves remaining: " << (wolves - i) << "\n\nHit enter to continue" <<
std::endl;
							std::string t;
							std::getline(std::cin, t);
						}
					}
					while (true);
				}
				return true;
			})
		})
	));

	Party party;
	prologue(party);
	return 0;
}
