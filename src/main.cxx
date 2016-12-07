#include "Page.hxx"
#include "Player.hxx"
#include "Chapter.hxx"

#include <map>
#include <cctype>
#include <locale>
#include <iostream>
#include <algorithm> 
#include <functional> 

using namespace std;
using namespace tbrg3;

 
// trim from start
static inline
string &
ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
            not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline
string &
rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(),
            not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline
string &
trim(string &s) {
    return ltrim(rtrim(s));
}

// Consider making this into a separate class for more functionality
map<string, Player> party;

int
main (int argc, char **argv)
{
	Chapter prologue("\n\n\t_PROLOGUE_\n\n", {
		Page([]{
			cout << "Give me your name" << endl << ">> ";
			string name;
			getline(cin, name);
			trim(name);
			if (name.empty()) name = "Player";
			party[name] = Player();
			cout << "Alright " << name << "! Give me three other names for your fellow party members" << endl;
			for (int i = 0; i < 3; ++i) {
				while (true) {
					cout << (i + 1) << ">> ";
					getline(cin, name);
					trim(name);
					if (name.empty()) name = "Player";
					if (party.find(name) != party.end()) {
						cout << "There is already a party member with the name " << name
							<< "." << endl << "Try again" << endl;
					} else break;
				}
				party[name] = Player();
			}
		})
	});

	prologue();
	return 0;
}
