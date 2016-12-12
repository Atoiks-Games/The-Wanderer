/**
  * utils_str.cxx -- The str namespace of the utilities
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
	namespace str
	{
		void
		ltrim(std::string &s)
		{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(),
						std::not1(std::ptr_fun<int, int>(std::isspace))));
		}

		void
		rtrim(std::string &s)
		{
			s.erase(std::find_if(s.rbegin(), s.rend(),
						std::not1(std::ptr_fun<int, int>(
								std::isspace))).base(), s.end());
		}

		void
		trim(std::string &s)
		{
			rtrim(s);
			ltrim(s);
		}

		bool
		iequals(const std::string &a, const std::string &b)
		{
			if (a.length() == b.length())
			{
				return std::equal(b.begin(), b.end(), a.begin(),
						[](char a, char b)
						{
							return std::tolower(a) == std::tolower(b);
						});
			}
			return false;
		}
	};
};
