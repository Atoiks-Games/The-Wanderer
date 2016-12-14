/**
  * Wolf.cxx -- A wolf. (Not a pack, just one)
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

#include "Enemies.hxx"

namespace wanderer
{
	namespace enemies
	{
		Wolf::Wolf()
			: Player()
		{
			gen_stats();
		}

		Wolf::~Wolf()
		{
		}

		void
		Wolf::gen_stats()
		{
			base_stats(*this);
			strength -= 5;
			if (strength < 3) strength = 3;
			hitpoints = 7;
		}

		std::string
		Wolf::default_greeter()
		{
			return "Wooof!";
		}

		std::string
		Wolf::class_name()
		{
			return "Wolf";
		}
	};
};
