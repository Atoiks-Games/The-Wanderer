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

std::string
tbrg3::players::Elf::default_greeter()
{
	return "You are now an elf! A very popular choice...";
}
