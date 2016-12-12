#include "Player.hxx"

tbrg3::players::Human::Human()
	: Player()
{
}

tbrg3::players::Human::~Human()
{
}

void
tbrg3::players::Human::gen_stats()
{
	base_stats(*this);
	charisma += 2;
	strength += 1;
	wisdom -= 1;
}

std::string
tbrg3::players::Human::default_greeter()
{
	return "Yay! (Goes back to doing Human stuff, you know...)";
}
