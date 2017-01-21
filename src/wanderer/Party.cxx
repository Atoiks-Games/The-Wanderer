/**
  * Party.cxx -- A group of players
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

#include "Party.hxx"

namespace wanderer
{
	Party::Party()
		: players(), merchantFlag(false)
	{
	}

	Party::Party(const Party &ref)
		: players(ref.players), merchantFlag(ref.merchantFlag)
	{
	}

	Party::Party(Party &&mref)
		: Party()
	{
		swap(*this, mref);
	}

	Party::~Party()
	{
	}

	Party &
	Party::operator=(Party ref)
	{
		swap(*this, ref);
		return *this;
	}

	std::shared_ptr<Player>
	Party::find_player(std::string name)
	{
		auto pl = players.find(name);
		if (pl == players.end()) return std::shared_ptr<Player>(nullptr);
		return pl->second;
	}

	const std::shared_ptr<Player>
	Party::find_player(std::string name) const
	{
		auto pl = players.find(name);
		if (pl == players.end()) return std::shared_ptr<Player>(nullptr);
		return pl->second;
	}

	std::shared_ptr<Player>
	Party::remove_player(std::string name)
	{
		auto pl = players.find(name);
		if (pl == players.end()) return std::shared_ptr<Player>(nullptr);
		auto ret = pl->second;
		players.erase(pl);
		return ret;
	}

	std::shared_ptr<Player> &
	Party::operator[](std::string name)
	{
		return players[name];
	}

	std::map<std::string, std::shared_ptr<Player>>::iterator
	Party::begin()
	{
		return players.begin();
	}
	
	std::map<std::string, std::shared_ptr<Player>>::iterator
	Party::end()
	{
		return players.end();
	}

	std::map<std::string, std::shared_ptr<Player>>::const_iterator
	Party::begin() const
	{
		return players.cbegin();
	}
	
	std::map<std::string, std::shared_ptr<Player>>::const_iterator
	Party::end() const
	{
		return players.cend();
	}

	void
	Party::erase(std::map<std::string, std::shared_ptr<Player>>::iterator it)
	{
		players.erase(it);
	}

	void
	Party::clear()
	{
		players.clear();
	}

	void
	Party::enableMerchant()
	{
		this->merchantFlag = true;
	}

	void
	Party::disableMerchant()
	{
		this->merchantFlag = false;
	}

	bool
	Party::empty() const
	{
		return players.empty();
	}

	std::size_t
	Party::size() const
	{
		return players.size();
	}

	bool
	Party::hasMerchant() const
	{
		return this->merchantFlag;
	}

	void
	swap(Party &lhs, Party &rhs)
	{
		using std::swap;

		swap(lhs.players, rhs.players);
		swap(lhs.merchantFlag, rhs.merchantFlag);
	}
};
