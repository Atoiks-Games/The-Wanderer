/**
  * Players.hxx -- A list of useful characters
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

#ifndef __THE_WANDERER_PLAYERS_H__
#define __THE_WANDERER_PLAYERS_H__

#include "Player.hxx"

namespace wanderer
{
	namespace players
	{
		class Dwarf : public Player
		{
		public:
			Dwarf();
			~Dwarf();
			void gen_stats();
			std::string default_greeter() const;
			std::string class_name() const;
		};

		class Human : public Player
		{
		public:
			Human();
			~Human();
			void gen_stats();
			std::string default_greeter() const;
			std::string class_name() const;
		};

		class Elf : public Player
		{
		public:
			Elf();
			~Elf();
			void gen_stats();
			std::string default_greeter() const;
			std::string class_name() const;
		};

		class Gnome : public Player
		{
		public:
			Gnome();
			~Gnome();
			void gen_stats();
			std::string default_greeter() const;
			std::string class_name() const;
		};

		class Infernal : public Player
		{
		public:
			Infernal();
			~Infernal();
			void gen_stats();
			std::string default_greeter() const;
			std::string class_name() const;
		};

		class Lizardfolk : public Player
		{
		public:
			Lizardfolk();
			~Lizardfolk();
			void gen_stats();
			std::string default_greeter() const;
			std::string class_name() const;
		};
	};
};

#endif
