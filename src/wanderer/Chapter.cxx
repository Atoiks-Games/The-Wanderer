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

namespace wanderer
{
	Chapter::Chapter()
		: name(), pages(), next(nullptr)
	{
	}

	Chapter::Chapter(std::string _n, std::vector<Page> _p)
		: name(_n), pages(_p), next(nullptr)
	{
	}

	Chapter::Chapter(const Chapter &ref)
		: name(ref.name), pages(ref.pages), next(ref.next)
	{
	}

	Chapter::Chapter(Chapter &&mref)
		: Chapter()
	{
		swap(*this, mref);
	}

	Chapter::~Chapter()
	{
	}

	Chapter &
	Chapter::operator=(Chapter ref)
	{
		swap(*this, ref);
		return *this;
	}

	std::shared_ptr<Chapter>
	Chapter::get_next()
	{
		return this->next;
	}

	void
	Chapter::and_then(std::shared_ptr<Chapter> next)
	{
		this->next = next;
	}

	void
	Chapter::operator()(Party &info)
	{
		std::cout << name << std::endl;
		for (auto it = pages.begin(); it < pages.end(); ++it)
		{
			// Abort execution on false
			if (!((*it)(info))) return;
		}
		if (next != nullptr) (*next)(info);
	}

	void
	swap(Chapter &lhs, Chapter &rhs)
	{
		using std::swap;

		swap(lhs.name, rhs.name);
		swap(lhs.pages, rhs.pages);
		swap(lhs.next, rhs.next);
	}
};
