/**
  * Read.cxx -- Utiliies related to reading. This does use the wanderer classes
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

#include "Read.hxx"

namespace wanderer
{
	namespace read
	{
		std::string
		new_name(const Party &p, std::string prompt)
		{
			do
			{
				std::string name = utils::io::read_non_empty_line(prompt);
				if (name.find('&') != std::string::npos)
				{
					std::cout <<
"Names cannot contain '&' (ampersand sign)" << std::endl;
					continue;
				}
				if (p.find_player(name).get() == nullptr) return name;
				std::cout <<
"There is already a party member with the name " << name << ".\nTry again" <<
std::endl;
			}
			while (true);
		}

		std::unique_ptr<Player>
		race()
		{
			std::cout <<
"Pick a race between Dwarf, Human, Elf, Gnome, Infernal and Lizardfolk" <<
std::endl;
			do
			{
				const std::string str = utils::io::read_non_empty_line();
				if (utils::str::iequals("d", str)
						|| utils::str::iequals("dwarf", str))
				{
					return std::unique_ptr<Player>(new players::Dwarf());
				}
				if (utils::str::iequals("h", str)
						|| utils::str::iequals("human", str))
				{
					return std::unique_ptr<Player>(new players::Human());
				}
				if (utils::str::iequals("e", str)
						|| utils::str::iequals("elf", str))
				{
					return std::unique_ptr<Player>(new players::Elf());
				}
				if (utils::str::iequals("g", str)
						|| utils::str::iequals("gnome", str))
				{
					return std::unique_ptr<Player>(new players::Gnome());
				}
				if (utils::str::iequals("i", str)
						|| utils::str::iequals("infernal", str))
				{
					return std::unique_ptr<Player>(new players::Infernal());
				}
				if (utils::str::iequals("l", str)
						|| utils::str::iequals("lizardfolk", str))
				{
					return std::unique_ptr<Player>(new players::Lizardfolk());
				}
				std::cout << "No race was associated with " << str << std::endl;
			}
			while (true);
		}

		std::string
		name_of_player(const Party &p, std::string prompt)
		{
			do
			{
				std::cout << prompt <<
" Write the character's full name" << std::endl;
				const std::string name = utils::io::read_non_empty_line();
				if (name.find('&') != std::string::npos)
				{
					std::cout <<
"Only one name. & does not work in this context!" << std::endl;
					continue;
				}
				if (p.find_player(name).get() == nullptr)
				{
					std::cout <<
"Maybe you suck at spelling, because no one is called " << name <<
"\nChoices:\n";
					for (auto it = p.begin(); it != p.end(); ++it)
					{
						std::cout << it->first <<
'(' << it->second->class_name() << ")\n";
					}
					std::cout << std::endl;
				}
				else return name;
			}
			while (true);
		}

		std::vector<std::string>
		name_of_players(const Party &p, std::string prompt)
		{
			do
			{
reread_input:
				std::cout << prompt << " Write the character's full name\n"
"Use '&' (the ampersand) in between names to specify more than one" <<
std::endl;
				const std::string name = utils::io::read_non_empty_line();
				std::vector<std::string> names = utils::str::split(name, '&');
				if (names.empty())
				{
					std::cout <<
"You need to at least supply one name" << std::endl;
					goto reread_input;
				}

				for (auto it = names.begin(); it != names.end(); ++it)
				{
					utils::str::trim(*it);
					if (p.find_player(*it).get() == nullptr)
					{
						std::cout <<
"Maybe you suck at spelling, because no one is called " << name <<
"\nChoices:\n";
						for (auto it = p.begin(); it != p.end(); ++it)
						{
							std::cout << it->first <<
'(' << it->second->class_name() << ")\n";
						}
						std::cout << std::endl;
						goto reread_input;
					}
				}
				return names;
			}
			while (true);
		}
	};
};
