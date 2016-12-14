/**
  * Player.hxx -- An individual Playable Character
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

#ifndef __THE_WANDERER_PLAYER_H__
#define __THE_WANDERER_PLAYER_H__

#include <string>
#include <random>
#include <sstream>

namespace wanderer
{
	class Player
	{
	protected:
		int strength;
		int dexterity;
		int constitution;
		int intelligence;
		int wisdom;
		int charisma;
	public:
		int hitpoints;

		Player();
		virtual ~Player();
		virtual void gen_stats() = 0;
		virtual std::string get_stats() const final;
		virtual std::string default_greeter() = 0;
		virtual std::string class_name() = 0;

		virtual int gen_attack_to_hit() const final;
		virtual int gen_chance_to_avoid() const final;

		virtual bool attack(Player &p) final;

		friend void base_stats(Player &p);
	};
};

#endif
