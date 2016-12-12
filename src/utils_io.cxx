/**
  * utils_io.cxx -- The io namespace of the utilities
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

#include "Utils.hxx"

namespace utils
{
	namespace io
	{
		std::string
		read_non_empty_line(std::string prompt)
		{
			std::string str;
			while (true)
			{
				std::cout << prompt;
				std::getline(std::cin, str);
				utils::str::trim(str);
				if (!str.empty()) return str;
			}
		}
	};
};
