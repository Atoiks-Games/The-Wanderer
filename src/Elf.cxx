#include "Player.hxx"

tbrg3::players::Elf::Elf()
	: Player()
{
}

tbrg3::players::Elf::~Elf()
{
}

void
tbrg3::players::Elf::gen_stats()
{
	base_stats(*this);
	intelligence += 2;
	dexterity += 1;
	constitution -= 1;
}
