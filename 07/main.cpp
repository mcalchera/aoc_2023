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
};

Hand process_line(string line) {
  istringstream ss(line);
  string h,b;
  ss >> h >> b;
  Hand hand = { h, stoi(b) }; 

  return hand;
}

int hand_type (Hand hand) {

    return 0;
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
