/**
  * Events.hxx -- Some main events in the storyline
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

#ifndef __THE_WANDERER_EVENTS_HXX__
#define __THE_WANDERER_EVENTS_HXX__

#include "Read.hxx"
#include "Utils.hxx"
#include "Party.hxx"
#include "Enemies.hxx"

#include <memory>
#include <string>
#include <vector>
#include <functional>

namespace wanderer
{
	namespace events
	{
		template <typename T>
		bool
		combat(std::vector<T> &pack, Party &p, std::string name,
			   std::function<void(std::string)> on_player_death,
			   std::function<bool(std::string)> after_player_death,
			   std::function<void(std::string)> on_player_got_hit,
			   std::function<void(std::string)> on_player_dodge,
			   std::function<void(std::string)> on_enemy_got_hit,
			   std::function<void(std::string)> on_enemy_dodge,
			   std::function<void(std::string, std::shared_ptr<Player>)> status)
		{
			if (pack.empty()) return true;
			auto player = p.find_player(name);
			for (auto it = pack.begin(); it != pack.end(); )
			{
				do
				{
					if (it->attack(*player))
					{
						if (player->hitpoints < 1)
						{
							on_player_death(name);
							p.remove_player(name);
							if (p.empty())
							{
								std::cout <<
"All party members are dead!" << std::endl;
								return false;
							}
							return after_player_death(name);
						}
						on_player_got_hit(name);
					}
					else on_player_dodge(name);

					if (player->attack(*it))
					{
						on_enemy_got_hit(name);
						if (it->hitpoints < 1)
						{
							it = pack.erase(it);
							std::cout << " and it is dead!\n" << std::endl;
							goto combat_loop_clean_up;
						}
					}
					else on_enemy_dodge(name);
combat_loop_clean_up:
					status(name, player);
					std::cout << "\nHit enter to continue" << std::endl;
					std::string t;
					std::getline(std::cin, t);
				}
				while (it != pack.end());
			}
			return true;
		}

		bool send_player_to_parcel(Party &p);

		bool fight_skeleton(Party &p, std::string name);
	};
};

#endif
