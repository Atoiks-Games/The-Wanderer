/**
  * Utils.hxx -- Useful utilities
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

#ifndef __TBRG_3_UTILS_HXX__
#define __TBRG_3_UTILS_HXX__

#include <cctype>
#include <locale>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

namespace utils
{
	namespace str
	{
		void ltrim(std::string &s);
		void rtrim(std::string &s);
		void trim(std::string &s);
		bool iequals(const std::string &a, const std::string &b);
	};
	namespace io
	{
		std::string read_non_empty_line(std::string prompt = ">> ");
	};
};

#endif
