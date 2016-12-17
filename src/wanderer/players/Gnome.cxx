/**
  * Gnome.cxx -- A playable character with the race of gnome
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

#include "Players.hxx"

wanderer::players::Gnome::Gnome()
	: Player()
{
	gen_stats();
}

wanderer::players::Gnome::~Gnome()
{
}

void
wanderer::players::Gnome::gen_stats()
{
	base_stats(*this);
	dexterity += 2;
	charisma += 1;
	strength -= 1;
}

std::string
wanderer::players::Gnome::default_greeter() const
{
	return "You are now a gnome! How cute!";
}

std::string
wanderer::players::Gnome::class_name() const
{
	return "Gnome";
}
