#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>

#include "../include/args.h"

using namespace std;

int calculate_score(vector<int> winners, vector<int> card, int &num_winners) {
  sort(winners.begin(), winners.end());
  sort(card.begin(), card.end());
  vector<int> intersection;
  set_intersection(winners.begin(), winners.end(),
                   card.begin(), card.end(),
                   back_inserter(intersection));

  num_winners = intersection.size();
  if (num_winners > 0 ) {
    return pow(2, num_winners - 1);
  }
  return 0;
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  int part1 = 0;
  int part2 = 0;
  map<int,int> winner_list;
  map<int,int> num_cards;
  vector<string> cards;
  ifstream in(argv[1]);

  if (in.good()) {
    string line;
    int line_num = 0;
    while (getline(in,line)) {
      cards.push_back(line);
    }
    // part 1
    for (auto line : cards) {
      ++line_num;
      vector<int> winners;
      vector<int> nums;
      string tmp;
      auto ss = istringstream(line);
      getline(ss,tmp,':');
      getline(ss,tmp,':');
      ss = istringstream(tmp);
      while (ss >> tmp) {
        if (tmp == "|") {
          break;
        }
        winners.push_back(stoi(tmp));
      }
      while (ss >> tmp) {
        nums.push_back(stoi(tmp));
      }
      int num_winners = 0;
      int line_score = calculate_score(winners,nums, num_winners);
      part1 += line_score;
      winner_list[line_num] = num_winners;
      num_cards[line_num] = 1; 
    }
    for (int i = 1; i <= line_num; ++i) {
      for (int j = i+1; j <= i + winner_list[i]; ++j) {
        num_cards[j] += num_cards[i];
      }
    }
  }
  for (auto it = num_cards.begin(); it != num_cards.end(); ++it) {
    part2 += it->second;
  }

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
