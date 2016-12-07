#include "Chapter.hxx"

tbrg3::Chapter::Chapter(std::string _n, std::vector<Page> _p)
	: name(_n), pages(_p), next(nullptr)
{
}

tbrg3::Chapter::~Chapter()
{
}

void
tbrg3::Chapter::and_then(std::shared_ptr<Chapter> next)
{
	this->next = next;
}

void
tbrg3::Chapter::operator()()
{
	std::cout << name << std::endl;
	for (auto it = pages.begin(); it < pages.end(); ++it) {
		(*it)();
	}
	if (next != nullptr) (*next)();
}
