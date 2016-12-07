#ifndef __TBRG_3_CHAPTER_H__
#define __TBRG_3_CHAPTER_H__

#include "Page.hxx"

#include <memory>
#include <vector>
#include <iostream>

namespace tbrg3
{
	class Chapter final
	{
	private:
		std::string name;
		std::vector<Page> pages;
		std::shared_ptr<Chapter> next;
	public:
		Chapter(std::string name, std::vector<Page> pages);
		~Chapter();
		void and_then(std::shared_ptr<Chapter> next);
		void operator()();
	};
};

#endif
