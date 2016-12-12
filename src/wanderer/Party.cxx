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
		: players()
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

	void
	swap(Party &lhs, Party &rhs)
	{
		using std::swap;

		swap(lhs.players, rhs.players);
	}
};
