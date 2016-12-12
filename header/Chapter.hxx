/**
  * Chapter.hxx -- An individual chapter of the story
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

#ifndef __THE_WANDERER_CHAPTER_H__
#define __THE_WANDERER_CHAPTER_H__

#include "Page.hxx"

#include <memory>
#include <vector>
#include <iostream>

namespace wanderer
{
	class Chapter final
	{
	private:
		std::string name;
		std::vector<Page> pages;
		std::shared_ptr<Chapter> next;
	public:
		Chapter(std::string name, std::vector<Page> pages);
		~Chapter();
		void and_then(std::shared_ptr<Chapter> next);
		void operator()();
	};
};

#endif
