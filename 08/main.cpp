#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include "../include/args.h"

using namespace std;

typedef vector<string> str_pair;
typedef map<string, str_pair> mapping;


void process_line(mapping & maps, string line) {
  istringstream ss(line);
  string start, left, right, part;
  
  ss >> start >> part >> left >> right;
  for (auto it = left.begin(); it != left.end();  ++it) {
    if (*it > 'Z' || *it < 'A') {
      left.erase(it);
      --it;
    }
  }
  for (auto it = right.begin(); it != right.end(); ++it) {
    if (*it > 'Z' || *it < 'A') {
      right.erase(it);
      --it;
    }
  }

  vector<string> pairs;
  pairs.push_back(left);
  pairs.push_back(right);

  maps[start] = pairs;  
}

bool finished(vector<string> nodes) {
  
  for (auto str : nodes) {
    if (str[2] != 'Z') {
      return false;
    }
  }
  return true;
}

long gcd(long a, long b) {
  return b == 0 ? a : gcd(b, a % b);
}

long lcm(long a, long b) {
  return a * b / gcd(a,b);
}

vector<string> get_starts(mapping maps) {
  string s;
  vector<string> vec;
  for (auto it = maps.begin(); it != maps.end(); ++it) {
    s = it->first;
    if ( s[2] == 'A') {
      vec.push_back(s);
    }
  }
  return vec;
}
int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  ifstream in(argv[1]);
  string directions;
  mapping maps;

  if (!in.good()) {
    return -1;
  }
  
  // Begin input processing
  getline(in, directions);
  
  string line;
  getline(in, line); // throw away empty line

  while (getline(in,line)) {
    process_line(maps, line);
  }
  // End input processing

  string current = "AAA";
  long part1 = 0, part2 = 1;
  auto dir_it = directions.begin();

  while ( current != "ZZZ" ) {
    ++part1;
    // go back to beginning of directions if you're at the end
    if (dir_it == directions.end()) {
      dir_it = directions.begin();
    }

    const size_t dir = (*dir_it == 'R') ? 1 : 0;
    current = maps[current][dir];
    ++dir_it;
  }
  
  // part2
  vector<string> starts = get_starts(maps);
  map <string,int> distance;
  for (auto n : starts) {
    string s = n;
    dir_it = directions.begin();
    while (s[2] != 'Z') {

      if(dir_it == directions.end()) {
        dir_it = directions.begin();
      }
      const size_t dir = (*dir_it == 'R') ? 1 : 0;
      ++distance[n];
      
      s = maps[s][dir];  
     
      ++dir_it;
    }
  }

  for (auto &[start, dist] : distance) {
    part2 = lcm(part2, dist);
  }



  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
