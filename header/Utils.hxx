#ifndef __TBRG_3_UTILS_HXX__
#define __TBRG_3_UTILS_HXX__

#include <cctype>
#include <locale>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

namespace utils
{
	namespace str
	{
		void ltrim(std::string &s);
		void rtrim(std::string &s);
		void trim(std::string &s);
		bool iequals(const std::string &a, const std::string &b);
	};
	namespace io
	{
		std::string read_non_empty_line(std::string prompt = ">> ");
	};
};

#endif
