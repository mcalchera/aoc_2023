#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdlib>
#include "../include/args.h"

using namespace std;

map<char,int> face_values = {
  { 'A', 14 },
  { 'K', 13 },
  { 'Q', 12 },
  { 'J', 11 },
  { 'T', 10 }
};

struct Hand {
  string hand;
  int bid;
  int type;

  // hands are ranked
  // 5 of a kind = 6
  // 4 of a kind = 5
  // full house = 4
  // 3 of a kind = 3
  // 2 pair = 2
  // 2 of a kind = 1
  // high card = 0
  void set_hand_type() {
    string cards = hand;
    map<char,int> ch_count;
    vector<int> counts;

    // count how many time each character shows up
    for (auto ch : cards) {
      ++ch_count[ch];
    }
    for (auto it = ch_count.begin(); it != ch_count.end(); ++it) {
      counts.push_back(it->second);
    }
    //reverse sort counts
    sort(counts.rbegin(),counts.rend());
   
    if (counts[0] == 5) {
      type = 6;
    }
    else if (counts[0] == 4) {
      type = 5;
    }
    else if (counts[0] == 3 && counts[1] == 2) {
      type = 4;
    }
    else if (counts[0] == 3) {
      type = 3;
    }
    else if (counts[0] == counts[1]) {
      type = 2;
    }
    else if (counts[0] == 2) {
      type = 1;
    }
    else {
      type = 0;
    }
  }
};

Hand process_line(string line) {
  istringstream ss(line);
  string h,b;
  ss >> h >> b;
  Hand hand = { h, stoi(b) }; 
  hand.set_hand_type();
  return hand;
}


int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  ifstream in(argv[1]);
  string line;
  vector<Hand> hands;

  if (!in.good()) {
    in.close();
    return -1;
  }
  
  while (getline(in, line)) {
    hands.push_back(process_line(line));
  }
  in.close();


  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
