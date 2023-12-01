#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <stdlib.h>
#include "../include/args.h"

using namespace std;

int find_num(string str, int dir) {
  static map<string,int> nummap;
  nummap["one"] = 1;
  nummap["two"] = 2;
  nummap["three"] = 3;
  nummap["four"] = 4;
  nummap["five"] = 5;
  nummap["six"] = 6;
  nummap["seven"] = 7;
  nummap["eight"] = 8;
  nummap["nine"] = 9;
  nummap["zero"] = 0;

  for (auto i = (dir == 1) ? 0 : str.length() -1; ; i += dir) {
    for (auto it = nummap.begin(); it != nummap.end(); ++it) {
      if (str[i] == it->second + '0') {
        return it-> second;
      }
      if (str.substr(i, it->first.length()) == it->first) {
        return it->second;
      }
    }

  }
}

void process_line(string str, int &first, int &last) {
  for (auto it = str.begin(); it != str.end(); ++it) {
    char c = *it;
    if (isdigit(c)) { 
      if (first == -1 ) { // first not initialized yet
        first = c - '0';
        last = first;
      }
      else { // first initialized, this is a new number
        last = c - '0';
      }
    }
  }
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  long total = 0;
  long total2 = 0;
  ifstream in;
  string str;
  in.open(argv[1]);

  if (in.good()) {
    while ( getline(in,str)) {
      int first = -1,last = -1;
      process_line(str, first, last);
      total += first * 10 + last;
    }

    // Part 2
    in.clear();
    in.seekg(0);
    while ( getline(in,str)) {
      int first = find_num(str,1);
      int last = find_num(str, -1);
      total2 += first * 10 + last;
    }
  }
  
  cout << "Part 1: " << total << endl << "Part 2: " << total2 << endl;
  return 0;
}
