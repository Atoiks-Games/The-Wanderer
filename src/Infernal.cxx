#include "Player.hxx"

tbrg3::players::Infernal::Infernal()
	: Player()
{
}

tbrg3::players::Infernal::~Infernal()
{
}

void
tbrg3::players::Infernal::gen_stats()
{
	base_stats(*this);
	wisdom += 2;
	intelligence += 1;
	charisma -= 1;
}
