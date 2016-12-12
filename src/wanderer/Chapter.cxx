/**
  * Chapter.cxx -- An individual chapter of the story
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

#include "Chapter.hxx"

wanderer::Chapter::Chapter(std::string _n, std::vector<Page> _p)
	: name(_n), pages(_p), next(nullptr)
{
}

wanderer::Chapter::~Chapter()
{
}

void
wanderer::Chapter::and_then(std::shared_ptr<Chapter> next)
{
	this->next = next;
}

void
wanderer::Chapter::operator()()
{
	std::cout << name << std::endl;
	for (auto it = pages.begin(); it < pages.end(); ++it) {
		(*it)();
	}
	if (next != nullptr) (*next)();
}