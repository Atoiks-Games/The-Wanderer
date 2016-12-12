#ifndef __TBRG_3_PLAYER_H__
#define __TBRG_3_PLAYER_H__

#include <string>
#include <random>

namespace tbrg3
{
	class Player
	{
	protected:
		int strength;
		int dexterity;
		int constitution;
		int intelligence;
		int wisdom;
		int charisma;
	public:
		Player();
		virtual ~Player();
		virtual void gen_stats() = 0;

		friend void base_stats(Player &p);
	};

	namespace players
	{
		class Dwarf : public Player
		{
		public:
			Dwarf();
			~Dwarf();
			void gen_stats();
		};

		class Human : public Player
		{
		public:
			Human();
			~Human();
			void gen_stats();
		};

		class Elf : public Player
		{
		public:
			Elf();
			~Elf();
			void gen_stats();
		};

		class Gnome : public Player
		{
		public:
			Gnome();
			~Gnome();
			void gen_stats();
		};

		class Infernal : public Player
		{
		public:
			Infernal();
			~Infernal();
			void gen_stats();
		};

		class Lizardfolk : public Player
		{
		public:
			Lizardfolk();
			~Lizardfolk();
			void gen_stats();
		};
	};
};

#endif
