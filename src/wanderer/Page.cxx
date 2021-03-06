/**
  * page.cxx -- This goes under individuall chapters
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

#include "Page.hxx"

namespace wanderer
{
	Page::Page(std::function<bool(Party&)> _act)
		: act(_act)
	{
	}

	Page::Page(const Page &ref)
		: act(ref.act)
	{
	}

	Page::Page(Page &&mref)
		: Page()
	{
		swap(*this, mref);
	}

	Page::~Page()
	{
	}

	Page &
	Page::operator=(Page ref)
	{
		swap(*this, ref);
		return *this;
	}

	bool
	Page::operator()(Party &info)
	{
		return act(info);
	}

	void
	swap(Page &lhs, Page &rhs)
	{
		using std::swap;

		swap(lhs.act, rhs.act);
	}
};
