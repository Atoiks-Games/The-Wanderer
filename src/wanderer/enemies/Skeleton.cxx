/**
  * Skeleton.cxx -- A skeleton
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
		Skeleton::Skeleton()
			: Player()
		{
			gen_stats();
		}

		Skeleton::~Skeleton()
		{
		}

		void
		Skeleton::gen_stats()
		{
			base_stats(*this);
			strength -= 5;
			intelligence -= 2;
			dexterity -= 3;
			if (strength < 3) strength = 3;
			hitpoints = 13;
		}

		std::string
		Skeleton::default_greeter() const
		{
			return "Crackle~";
		}

		std::string
		Skeleton::class_name() const
		{
			return "Skeleton";
		}
	};
};
