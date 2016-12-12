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

std::string
tbrg3::players::Infernal::default_greeter()
{
	return "Is it me or is it getting hot in here?";
}
