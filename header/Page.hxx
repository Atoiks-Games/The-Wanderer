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

#ifndef __TBRG_3_PAGE_H__
#define __TBRG_3_PAGE_H__

#include <functional>

namespace tbrg3
{
	class Page final
	{
	private:
		std::function<void(void)> act;
	public:
		Page(std::function<void(void)> act = []{});
		~Page();
		void operator()();
	};
};

#endif
