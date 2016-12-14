/**
  * page.hxx -- This goes under individual chapters
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

#ifndef __THE_WANDERER_PAGE_H__
#define __THE_WANDERER_PAGE_H__

#include "Party.hxx"

#include <memory>
#include <algorithm>
#include <functional>

namespace wanderer
{
	class Page final
	{
	private:
		std::function<bool(Party&)> act;
	public:
		Page(std::function<bool(Party&)> act = [](Party &_r){ return true; });
		Page(const Page &ref);
		Page(Page &&mref);
		~Page();

		Page &operator=(Page ref);
		bool operator()(Party &info);

		friend void swap(Page &lhs, Page &rhs);
	};
};

#endif
