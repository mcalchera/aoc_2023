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

map<char,int> values = {
  { 'A', 14 },
  { 'K', 13 },
  { 'Q', 12 },
  { 'J', 11 },
  { 'T', 10 },
  { '9', 9 },
  { '8', 8 },
  { '7', 7 },
  { '6', 6 },
  { '5', 5 },
  { '4', 4 },
  { '3', 3 },
  { '2', 2 }
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
  void set_hand_type(int part = 1) {
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
    else if (counts[0] == counts[1] && counts[0] == 2) {
      type = 2;
    }
    else if (counts[0] == 2) {
      type = 1;
    }
    else {
      type = 0;
    }
    if (part == 2) { 
      // Deal with jokers for pt2
      int jokers = 0;
      int type2 = 0;
      for (auto ch : cards) { 
        jokers = ch == 'J' ? jokers + 1 : jokers;
      }

      // 4 of a kind - 5 
      // - if jokers -> 5 of a kind (6)
      // full house - 4
      // - if jokers -> 5 of a kind (6)
      // 3 of a kind - 3
      // - if jokers -> 4 of a kind (5)
      // 2 pair - 2
      //  - 1J -> Full house (4)
      //  - 2J -> 4 of a kind (5)
      // 1 pair - 1
      //  - always 3 of a kind (3)
      // High card = 0
      //  - alway pair (1)
      if (jokers > 0) {
        if (type == 0) {
          type2 = 1;
        }
        else if (type == 1) {
          type2 = 3;
        } 
        else if (type == 2 ) {
          if (jokers == 1) {
             type2 = 4;
          }
          else {
            type2 = 5;
          }
        }
        else if (type >= 3) {
          type2 = min(6, type+2);
        }
      }
      else { 
        type2 = type;
      }
      
      type = type2;
    }
  }
};


bool comp(Hand h1, Hand h2) {
  // Hands have the same rank
  if (h1.type == h2.type) {
    string s1 = h1.hand;
    string s2 = h2.hand;
    for (int i = 0; i < h1.hand.size(); ++i) {
      if (values[s1[i]] != values[s2[i]]) {
        return values[s1[i]] < values[s2[i]];
      }
    }
    return values[s1[0]] < values[s2[0]];

  }
  else {
    return h1.type < h2.type;
  }

}

Hand process_line(string line) {
  istringstream ss(line);
  string h,b;
  ss >> h >> b;
  Hand hand = { h, stoi(b) }; 
  hand.set_hand_type();
  return hand;
}

int get_winnings(vector<Hand> hands, int part = 1) {
  if (part == 2) {
    values['J'] = 0;
  }
  int val = 0;
  sort(hands.rbegin(), hands.rend(), comp);

  int mult = hands.size();
  for (auto it = hands.begin(); it != hands.end(); ++it) {
    val += mult * it->bid;
    --mult;
  }
  return val;
}

vector<Hand> part2_vec(vector<Hand> orig) {
  vector<Hand> n;
  Hand h;
  for (auto o : orig) {
    h.hand = o.hand;
    h.bid = o.bid;
    h.set_hand_type(2);
    n.push_back(h);
  }

  return n;
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

  
  cout << "Part 1: " << get_winnings(hands) << endl;
  vector<Hand> hands2 = part2_vec(hands);
  
  cout << "Part 2: " << get_winnings(hands2, 2) << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
