#include "Page.hxx"

tbrg3::Page::Page(std::function<void(void)> _act)
	: act(_act)
{
}

tbrg3::Page::~Page()
{
}

void
tbrg3::Page::operator()()
{
	act();
}
