/**
  * Inventory.cxx -- Storage for items and coins
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

#include "Inventory.hxx"

static constexpr int MAX_COINS = 256000;

namespace wanderer
{
	Inventory::Inventory()
		: coins(), items()
	{
	}

	Inventory::Inventory(const Inventory &ref)
		: coins(ref.coins), items(ref.items)
	{
	}

	Inventory::Inventory(Inventory &&mref)
		: Inventory()
	{
		swap(*this, mref);
	}

	Inventory::~Inventory()
	{
	}

	Inventory &
	Inventory::operator=(Inventory ref)
	{
		swap(*this, ref);
		return *this;
	}

	int
	Inventory::get_coins()
	{
		return coins;
	}

	int
	Inventory::deposit(int val)
	{
		if (val > 0)
		{
			coins += val;
			if (coins > MAX_COINS) coins = MAX_COINS;
		}
		return coins;
	}

	int
	Inventory::withdraw(int val)
	{
		if (val > 0)
		{
			if (val > coins) return -1;
			else coins -= val;
		}
		return coins;
	}

	bool
	Inventory::empty() const
	{
		return items.empty();
	}

	void swap(Inventory &lhs, Inventory &rhs)
	{
		using std::swap;

		swap(lhs.coins, rhs.coins);
		swap(lhs.items, rhs.items);
	}
};
