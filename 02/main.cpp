#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "../include/args.h"

using namespace std;

struct game_t {
  int red = 0;
  int green = 0;
  int blue = 0;
}; 

int main (int argc, char ** argv) {
  process_args(argc, argv);
  game_t pt1_max = {12, 13, 14};

  ifstream in;
  in.open(argv[1]);
  string line;
  vector<game_t> games;
  int total = 0;
  regex draw("(\\d+)\\s(red|green|blue)");

  if (in.good()) {
    while (getline(in,line)) {
      game_t game;
      auto iss = istringstream(line);
      string str;
      getline(iss, str, ':');
      getline(iss, str, ':');
      vector<string> tokens;
      auto ss = istringstream(str);
      while (getline(ss, str, ';')) {
        smatch match;
        while (regex_search(str, match, draw)) {
          int num = stoi(match[1]);
          string color = match[2];
          if (color == "red") {
            game.red = (num > game.red) ? num : game.red;
          }
          else if (color == "green") {
            game.green = (num > game.green) ? num : game.green;
          }
          else if (color == "blue") {
            game.blue = (num > game.blue) ? num : game.blue;
          }
          str = match.suffix().str();
        }
      }
      if (game.red != 0 && game.blue !=0 && game.green != 0 ) {
        games.push_back(game);
      }
    }
  }

  for (auto i = 0; i < games.size(); ++i) {
    total += (games[i].red <= pt1_max.red && games[i].green <= pt1_max.green && games[i].blue <= pt1_max.blue) ? i+1 : 0;
  }

  cout << "Part 1: " << total << endl;


  return 0;
}
