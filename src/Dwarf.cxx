#include "Player.hxx"

tbrg3::players::Dwarf::Dwarf()
  : Player()
{
  gen_stats();
}

tbrg3::players::Dwarf::~Dwarf()
{
}

void
tbrg3::players::Dwarf::gen_stats()
{
	base_stats(*this); 
	constitution += 2;
	strength += 1;
	dexterity -= 1;
}

std::string
tbrg3::players::Dwarf::default_greeter()
{
	return "You are now a dwarf! Diggy Diggy Hole!";
}
