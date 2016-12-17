/**
  * Party.hxx -- A group of players
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

#ifndef __THE_WANDERER_PARTY_HXX__
#define __THE_WANDERER_PARTY_HXX__

#include "Player.hxx"

#include <map>
#include <memory>
#include <string>
#include <algorithm>

namespace wanderer
{
	class Party final
	{
	private:
		std::map<std::string, std::shared_ptr<Player>> players;
	public:
		Party();
		Party(const Party &ref);
		Party(Party &&mref);
		~Party();

		Party &operator=(Party ref);

		std::shared_ptr<Player> find_player(std::string name);
		const std::shared_ptr<Player> find_player(std::string name) const;
		std::shared_ptr<Player> remove_player(std::string name);
		std::shared_ptr<Player> &operator[](std::string name);

		std::map<std::string, std::shared_ptr<Player>>::iterator begin();
		std::map<std::string, std::shared_ptr<Player>>::iterator end();
		std::map<std::string, std::shared_ptr<Player>>::const_iterator
		begin() const;
		std::map<std::string, std::shared_ptr<Player>>::const_iterator
		end() const;
		void erase(std::map<std::string, std::shared_ptr<Player>>::iterator it);

		bool empty() const;
		std::size_t size() const;

		friend void swap(Party &lhs, Party &rhs);
	};
};

#endif
