#include "Player.hxx"

tbrg3::Player::Player()
  : strength(0), dexterity(0), constitution(0), intelligence(0),
  wisdom(0), charisma(0)
{
}

tbrg3::Player::~Player()
{
}

namespace tbrg3
{
	void base_stats(Player &p)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> d(1, 6);
		p.strength = d(gen) + d(gen) + d(gen);
		p.dexterity = d(gen) + d(gen) + d(gen);
		p.constitution = d(gen) + d(gen) + d(gen);
		p.intelligence = d(gen) + d(gen) + d(gen);
		p.wisdom = d(gen) + d(gen) + d(gen);
		p.charisma = d(gen) + d(gen) + d(gen);
	}
};
