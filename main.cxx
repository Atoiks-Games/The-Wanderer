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
#include <vector>
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

std::string
read_name_of_player(const Party &party, std::string prompt)
{
	std::string name;
	do
	{
		std::cout << prompt << " Write the character's full name" << std::endl;
		name = io::read_non_empty_line();
		if (party.find_player(name).get() == nullptr)
		{
			std::cout <<
"Maybe you suck at spelling, because no one is called" << name <<
"\nChoices:\n";
			for (auto it = party.begin(); it != party.end(); ++it)
			{
				std::cout << it->first << '\n';
			}
			std::cout << std::endl;
			continue;
		}
		return name;
	}
	while (true);
}

bool parcel_send_player(Party &p);

bool parcel_on_wolf_killed_player(Party &p, const std::string &n, bool f=true);

bool
parcel_send_player(Party &party)
{
	std::cout <<
"Your party assembles down in the tavern. They speak among themselves, trying\n"
"to decide which party member should go out to get the parcel.\n";
	const std::string name = read_name_of_player(party, "Who should go?");
	std::cout <<
"Ok! You sent " << name << " to get the parcel" << std::endl;

	static std::vector<enemies::Wolf> pack(5);
	if (pack.empty()) goto no_wolves;

	if (pack.size() == 1)
	{
		std::cout << name << ": I see a wolf." << std::endl;
	}
	else
	{
		std::cout << name <<
": I see wolves. Wolves everywhere (" << pack.size() << " of them)!" <<
std::endl;
	}
	{
		auto player = party.find_player(name);
		for (auto it = pack.begin(); it != pack.end(); )
		{
			do
			{
				if (it->attack(*player))
				{
					if (player->hitpoints < 1)
					{
						std::cout << name <<
" did not make it...\nThe remaining wolves seemed to have went away" <<
std::endl;
						party.remove_player(name);
						if (party.empty())
						{
							std::cout <<
"All party members are dead!" << std::endl;
							return false;
						}

						std::random_device rd;
						std::mt19937 gen(rd());
						std::uniform_int_distribution<> d(1, 10);
						if (d(gen) > 6)
						{
							std::cout <<
"One of your party members 'senses' the death of " << name << std::endl;
							return parcel_on_wolf_killed_player(party, name);
						}

						std::cout <<
"\n\t...Five years later...\n\n" << name << " has not returned.\n"
"It is clear to the other group members that " << name << " is in trouble.\n";
						return parcel_on_wolf_killed_player(party, name, false);
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

				if (player->attack(*it))
				{
					std::cout << name << " hit the wolf";
					if (it->hitpoints < 1)
					{
						it = pack.erase(it);
						std::cout << " and it is dead!\n" << std::endl;
						goto combat_loop_clean_up;
					}
					std::cout << std::endl;
				}
				else
				{
					std::cout <<
"The wolf dodged " << name << "'s attack" << std::endl;
				}
				++it;
combat_loop_clean_up:
				std::cout <<
name << " has " << player->hitpoints << " hit points remaining\n"
"Wolves remaining: " << pack.size() << "\n\nHit enter to continue" << std::endl;
				std::string t;
				std::getline(std::cin, t);
			}
			while (it != pack.end());
		}
	}
no_wolves:
	std::cout << "You successfully acquired the parcel!" << std::endl;
	return true;
}

bool
parcel_on_wolf_killed_player(Party &p, const std::string &name, bool realize)
{
	if (realize) std::cout << p.begin()->first << ": " << name << " died! ";
	do
	{
		if (realize)
		{
			std::cout << "What do you want to do?\n\n-w Kill the wolves";
		}
		else
		{
			std::cout << "What do you want to do?\n";
		}
		std::cout << "\n-s Send another player\n-a Abort the mission"
"\n-c Try to kill the contractor" << std::endl;
		const std::string opt = io::read_non_empty_line();
		if (opt == "s") return parcel_send_player(p);
		if (opt == "a")
		{
			std::cout <<
"The contractor accepts your choice and then leaves" << std::endl;
			return false;
		}
		if (opt == "w" && realize)
		{
			std::cout << p.begin()->first <<
" failed to 'sense' any other wolves.";
			if (!p.empty())
			{
				std::cout <<
" The other members look at the player weird.";
			}
			std::cout << std::endl;
			continue;
		}
		if (opt == "c")
		{
			std::cout <<
"Turns out you are the contractor... You kill your fellow group mates and they"
"\nall died. DO NOT TRY TO KILL THE CONTRACTOR!" << std::endl;
			return false;
		}
		std::cout << "What is it?" << std::endl;
	}
	while (true);
	return true;
}

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
			return parcel_send_player(party);
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
"\t_NEWS HEADLINE: RESEARCHERS FIND ANCIENT ADVENTURERS FROZEN IN THE SNOW!_\n"
"\n(Your party members are the 'ancient adventurers' in case you didn't realize)" << std::endl;
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
						continue;
					}
					if (opt == "c")
					{
						const std::string name = read_name_of_player(p,
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
				}
				while (true);
				return true;
			}),
			Page([](Party &p){
				std::cout << "And you get there!" << std::endl;
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
