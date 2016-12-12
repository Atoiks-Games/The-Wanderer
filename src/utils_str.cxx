#include "Utils.hxx"

namespace utils
{
	namespace str
	{
		void
		ltrim(std::string &s)
		{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(),
						std::not1(std::ptr_fun<int, int>(std::isspace))));
		}

		void
		rtrim(std::string &s)
		{
			s.erase(std::find_if(s.rbegin(), s.rend(),
						std::not1(std::ptr_fun<int, int>(
								std::isspace))).base(), s.end());
		}

		void
		trim(std::string &s)
		{
			rtrim(s);
			ltrim(s);
		}

		bool
		iequals(const std::string &a, const std::string &b)
		{
			if (a.length() == b.length())
			{
				return std::equal(b.begin(), b.end(), a.begin(),
						[](char a, char b)
						{
							return std::tolower(a) == std::tolower(b);
						});
			}
			return false;
		}
	};
};
