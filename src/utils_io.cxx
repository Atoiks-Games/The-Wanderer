#include "Utils.hxx"

namespace utils
{
	namespace io
	{
		std::string
		read_non_empty_line(std::string prompt)
		{
			std::string str;
			while (true)
			{
				std::cout << prompt;
				std::getline(std::cin, str);
				utils::str::trim(str);
				if (!str.empty()) return str;
			}
		}
	};
};
