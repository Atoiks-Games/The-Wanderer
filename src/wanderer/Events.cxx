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
						if (names.size() == 1)
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
"(Just kiding, the wolves reappeared)\n" << std::endl;
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
		fight_skeleton(Party &p, std::vector<std::string> names)
		{
			static std::vector<enemies::Skeleton> guards(2);
			if (guards.empty()) return true;
			for (auto it = names.begin(); it != names.end(); ++it)
			{
				bool r = combat(guards, p, *it,
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
				if (r) return true;
			}
			return false;
		}

		bool
		cell_with_old_man_opt_t(Party &p)
		{
			bool enable_opt3;
			while (true) {
head:
				enable_opt3 = false;
				std::cout <<
"What do you say?\n\n-s Su dude!?\n"
"-a Are you the merchant we are looking for?\n-h Hey, are you alright?\n"
"-w What is your name?\n-d Don't worry. We are here to help!" << std::endl;

				const std::string opt = utils::io::read_non_empty_line();
				if (opt == "s") {
					std::cout <<
"The main fainted... You now decided to check the door because why not..." <<
std::endl;
					throw "ret";
				}
				if (opt == "a") {
					std::cout <<
"The man responds, Yes I am the lost merchant. Please get me out of the cell!"
<< std::endl;

sub_opt_no_2:
					while (true)
					{
						std::cout <<
"You have a choice between\n\n-a Ask more questions\n-d Inspect the door"
<< std::endl;
						if (enable_opt3)
						{
							std::cout <<
"-n Choose to not save the old man" << std::endl;
						}

						const std::string inner =
							utils::io::read_non_empty_line();
						if (inner == "a") goto head;
						if (inner == "d") throw "ret";
						if (enable_opt3 && inner == "n")
						{
							std::cout <<
"\"NO! WAIT PLZ!\"\n\n-e Leave\n-s Stay" << std::endl;
							const std::string inner2 =
								utils::io::read_non_empty_line();
							if (inner2 == "e")
							{
								std::cout <<
"You leave the merchant. He dies in the cave. You (apparently) do not care.\n"
"Unfortunately, you sense the journey will now be much harder without\n"
"someone to sell you items." << std::endl;
								return true; // game continues without merchant
							}
							if (inner2 != "s") std::cout <<
"You decide to stay even though that was not the order you were given..." <<
std::endl;
							goto head;
						}

						std::cout << "What is this?" << std::endl;
					}
					return true;
				}
				if (opt == "h") {
					std::cout <<
"The man looks at you like you are an idiot. \"I'm stuck in a cell! Of\n"
"course not!\"" << std::endl;
					enable_opt3 = true;
					goto sub_opt_no_2;
				}
				if (opt == "w") {
					std::cout <<
"My name if Jeef!" << std::endl;
					goto sub_opt_no_2;
				}
				if (opt == "d") {
					if (p.size() > 1)
					{
						std::cout <<
"I am the lost merchant. Please get me out of the cell!\n" <<
std::endl;
						goto sub_opt_no_2;
					}

					// Control flow would have been gone if party size was
					// greater than 1, so no need for else
					std::cout <<
"Wait we? There is only one of you..." << std::endl;
					while (true)
					{
						std::cout <<
"Choose a response\n\n-m That's what I want you to think\n"
"-s Oops, the others must have died, well I am here to rescue you! Are you\n"
"   the merchant we are looking for?" <<
std::endl;
						const std::string inner =
							utils::io::read_non_empty_line();
						if (inner == "m")
						{
							std::cout <<
"Shawdows turn into clones of you and they slowly converge on the man who\n"
"screams as he dies. Then you descend into the darkness never to be seen\n"
"again..." << std::endl;
							return false;
						}
						if (inner == "s") goto sub_opt_no_2;
						std::cout << "What is this?" << std::endl;
					}
				}
				std::cout << "What is this?" << std::endl;
			}
			return true;
		}

		bool
		cell_with_old_man_opt_d(Party &p)
		{
			std::cout <<
"The door speaks: 'HALT! WHO GOES THERE?'\nHow do you respond?\n\n"
"-s Su dude!?\n-m My name is " << p.begin()->first << ", also in my party ...\n"
"-w What are you?" << std::endl;

			std::cout <<
"Currently this does nothing, so yeah, you beat the game, and well, sure..." <<
std::endl;
			return true;
		}
	};
};
