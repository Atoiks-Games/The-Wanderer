/**
  * Player.cxx -- A playable character
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

#include "Player.hxx"

tbrg3::Player::Player()
  : strength(0), dexterity(0), constitution(0), intelligence(0),
  wisdom(0), charisma(0)
{
}

tbrg3::Player::~Player()
{
}

namespace tbrg3
{
	void base_stats(Player &p)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> d(1, 6);
		p.strength = d(gen) + d(gen) + d(gen);
		p.dexterity = d(gen) + d(gen) + d(gen);
		p.constitution = d(gen) + d(gen) + d(gen);
		p.intelligence = d(gen) + d(gen) + d(gen);
		p.wisdom = d(gen) + d(gen) + d(gen);
		p.charisma = d(gen) + d(gen) + d(gen);
	}
};
