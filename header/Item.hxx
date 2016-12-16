/**
  * Item.hxx -- Abstract class for items that can be stored in Inventory
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

#ifndef __THE_WANDERER_ITEM_H__
#define __THE_WANDERER_ITEM_H__

#include <string>

namespace wanderer
{
	class Item
	{
	public:
		Item();
		virtual ~Item();

		virtual bool operator<(const Item &rhs) const final;
		virtual std::string get_name() const = 0;
		virtual std::string get_desc() const = 0;
	};
};

#endif
