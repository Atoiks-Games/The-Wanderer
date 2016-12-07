#include "Page.hxx"
#include "Player.hxx"
#include "Chapter.hxx"

#include <map>
#include <cctype>
#include <locale>
#include <memory>
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

static inline
string
read_non_empty_line(string prompt = ">> ") {
  string str;
  while (true) {
    cout << prompt;
    getline(cin, str);
    trim(str);
    if (!str.empty()) return str;
  }
}

// Consider making this into a separate class for more functionality
map<string, Player> party;

int
main (int argc, char **argv)
{
	Chapter prologue("\n\n\t_PROLOGUE_\n\n", {
		Page([]{
			cout << "Give me your name" << endl;
			string name = read_non_empty_line();
			party[name] = Player();
			cout << "Alright " << name << "! Give me three other names for your fellow party members" << endl;
			for (int i = 0; i < 3; ++i) {
				while (true) {
          name = read_non_empty_line(to_string(i + 1) + ">> ");
					if (party.find(name) != party.end()) {
						cout << "There is already a party member with the name " << name
							<< "." << endl << "Try again" << endl;
					} else break;
				}
				party[name] = Player();
			}
		})
	});

  prologue.and_then(std::shared_ptr<Chapter>(
    new Chapter("\n\n\t_CHAPTER 1: The Missing Merchant_\n\n", {
      Page([]{
        cout << "Your party wakes up in their rooms of the inn. It's morning."
            << " They can hear the birds chirping and the nearby river flowing."
            << " They get out of bed and look around the tiny room they slept in."
            << endl
            << "As they begin to get dressed they remeber that their adventuring"
            << " contractor said he would be sending them a new task today."
            << " It would be in a parcel at the end of the long and twisted road"
            << " to the dropzone."
            << endl;
        while (true) {
          cout << endl << "What should your party do?" << endl << endl
              << "-i Inspect Their Rooms" << endl
              << "-m Meet up in The Tavern Below Their Rooms" << endl;
          string choice = read_non_empty_line();
          if (choice == "m" || choice == "M") {
            break;
          }
          if (choice == "i" || choice == "I") {
            cout << "Their rooms are small and dusty. Each character's"
                << " adventuring pack lays on the small bed. The window is opaque"
                << " with dust and grime. It isn't pretty, but it's cheap."
                << endl;
          } else {
            cout << "What is that?";
          }
        }
        while (true) {
          cout << "Your party assembles down in the tavern. They speak among"
              << " themselves, trying to decide which party member should go out"
              << " to get the parcel."
              << endl
              << "Who should go? Write the character's full name"
              << endl;
          string name = read_non_empty_line();
          if (party.find(name) == party.end()) {
            cout << "Maybe you suck at spelling, because no one with this name exists"
                << endl;
          } else {
            cout << "Ok! You sent " << name << " to get the parcel" << endl;
            break;
          }
        }
      })
    })
  ));

	prologue();
	return 0;
}
