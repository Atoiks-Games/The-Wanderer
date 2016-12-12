#include "Player.hxx"

tbrg3::players::Lizardfolk::Lizardfolk()
	: Player()
{
}

tbrg3::players::Lizardfolk::~Lizardfolk()
{
}

void
tbrg3::players::Lizardfolk::gen_stats()
{
	base_stats(*this);
	strength += 2;
	constitution += 1;
	charisma -= 1;
}
