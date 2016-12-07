#ifndef __TBRG_3_PAGE_H__
#define __TBRG_3_PAGE_H__

#include <functional>

namespace tbrg3
{
	class Page final
	{
	private:
		std::function<void(void)> act;
	public:
		Page(std::function<void(void)> act = []{});
		~Page();
		void operator()();
	};
};

#endif
