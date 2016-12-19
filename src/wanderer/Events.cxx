/**
  * Events.cxx -- Some main events in the storyline
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

#include "Events.hxx"

namespace wanderer
{
	namespace events
	{
		static
		bool
		__wolf_killed_player(Party &p, const std::string &name, bool realize=true)
		{
			if (realize)
			{
				std::cout << p.begin()->first << ": " << name << " died! ";
			}
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
				const std::string opt = utils::io::read_non_empty_line();
				if (opt == "s") return send_player_to_parcel(p);
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

		static
		bool
		__fight_wolves(std::vector<enemies::Wolf> &pack, Party &party,
					   std::vector<std::string>::iterator it,
					   const std::vector<std::string> names)
		{
			return combat(pack, party, *it,
					[](std::string n){
						std::cout << n <<
" did not make it...\nThe remaining wolves seemed to have went away" <<
std::endl;
					},
					[&party, &it, &pack, &names](std::string n){
						if (it == names.end())
						{
							std::random_device rd;
							std::mt19937 gen(rd());
							std::uniform_int_distribution<> d(1, 10);
							if (d(gen) > 6)
							{
								std::cout <<
"One of your party members 'senses' the death of " << n << std::endl;
								return __wolf_killed_player(party, n);
							}

							std::cout <<
"\n\t...Five years later...\n\n" << n << " has not returned.\n"
"It is clear to the other group members that " << n << " is in trouble.\n";
							return __wolf_killed_player(party, n, false);
						}
						std::cout <<
"(Just kiding, the wolves reappeared)" << std::endl;
						return __fight_wolves(pack, party, ++it, names);
					},
					[](std::string n){
						std::cout << n << ": Ouch!" << std::endl;
					},
					[](std::string n){
						std::cout << n << " dodged the wolf's attack" << std::endl;
					},
					[](std::string n){
						std::cout << n << " hit the wolf";
					},
					[](std::string n){
						std::cout <<
"The wolf dodged " << n << "'s attack" << std::endl;
					},
					[&pack](std::string n, std::shared_ptr<Player> player){
						std::cout <<
n << " has " << player->hitpoints << " hit points remaining\n"
"Wolves remaining: " << pack.size() << std::endl;
					});
		}

		bool
		send_player_to_parcel(Party &p)
		{
			std::cout <<
"Your party assembles down in the tavern. They speak among themselves, trying\n"
"to decide which party member should go out to get the parcel.\n";
			auto names = read::name_of_players(p, "Who should go?");
			if (names.size() == 1)
			{
				std::cout <<
"Ok! You sent " << names[0] << " to get the parcel" << std::endl;
			}
			else
			{
				std::cout <<
"Ok! You sent these people to get the parcel:\n";
				for (const std::string &name : names)
				{
					std::cout << name << '\n';
				}
			}

			static std::vector<enemies::Wolf> pack(5);
			if (pack.empty()) goto no_wolves;

			{
				auto it = names.begin();
				if (pack.size() == 1)
				{
					std::cout << *it << ": I see a wolf." << std::endl;
				}
				else
				{
					std::cout << *it <<
": I see wolves. Wolves everywhere (" << pack.size() << " of them)!" <<
std::endl;
				}
				return __fight_wolves(pack, p, it, names);
			}
no_wolves:
			std::cout << "You successfully acquired the parcel!" << std::endl;
			return true;
		}

		bool
		fight_skeleton(Party &p, std::string name)
		{
			static std::vector<enemies::Skeleton> guards(2);
			if (guards.empty()) return true;
			return combat(guards, p, name,
					[](std::string n){
						std::cout <<
n << " was slayed by the skeleton guards!" << std::endl;
					},
					[](std::string _n){
						return false;
					},
					[](std::string n){
						std::cout << n << ": Ouch!" << std::endl;
					},
					[](std::string n){
						std::cout <<
n << " dodged the blows of the skeleton guards." << std::endl;
					},
					[](std::string n){
						std::cout <<
n << " made the skeleton crack more than before" << std::endl;
					},
					[](std::string n){
						std::cout <<
"The skeleton guards dodged " << n << "'s attack" << std::endl;
					},
					[](std::string n, std::shared_ptr<Player> p){
						std::cout <<
n << " has " << p->hitpoints << " hit points remaining\n"
"Guards remaining: " << guards.size() << std::endl;
					});
		}
	};
};
