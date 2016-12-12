#include "Player.hxx"

tbrg3::players::Gnome::Gnome()
	: Player()
{
}

tbrg3::players::Gnome::~Gnome()
{
}

void
tbrg3::players::Gnome::gen_stats()
{
	base_stats(*this);
	dexterity += 2;
	charisma += 1;
	strength -= 1;
}
