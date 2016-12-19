/**
  * Read.hxx -- Utiliies related to reading. This use the wanderer classes
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

#ifndef __THE_WANDERER_READ_HXX__
#define __THE_WANDERER_READ_HXX__

#include "Party.hxx"
#include "Utils.hxx"
#include "Player.hxx"
#include "Players.hxx"

#include <memory>
#include <string>
#include <vector>

namespace wanderer
{
	namespace read
	{
		std::string new_name(const Party &p, std::string prompt = ">> ");
		std::unique_ptr<Player> race();
		std::string name_of_player(const Party &p, std::string prompt);
		std::vector<std::string>
		name_of_players(const Party &p, std::string prompt);
	};
};

#endif
