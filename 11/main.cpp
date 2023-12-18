#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include "../include/args.h"

using namespace std;

struct Galaxy {
  int x;
  int y;
};

set<int> get_empty_rows(vector<string> u) {
  set<int> r;
  for (int i = 0; i < u.size(); ++i) {
    if ( u[i].find("#") == string::npos) {  
      r.insert(i);
    }
  }
  return r;
}

set<int> get_empty_cols(vector<string> u) {
  set<int> r;
  for (int i = 0; i < u[0].size(); ++i) {
    bool empty = true;
    for (int j = 0; j < u.size(); ++j) {
      if (u[j][i] != '.') {
        empty = false;
      }
    }
    if (empty) {
      r.insert(i);
    }
  }
  return r;
}

vector<Galaxy> find_galaxies(vector<string> u) {
  vector<Galaxy> vec;
  for (int i = 0; i < u.size(); ++i) {
    for (int j = 0; j < u[i].size(); ++j) {
      if (u[i][j] == '#') {
        vec.push_back({ j, i });
      }
    }
  }
  return vec;
}

long manhattan_dist(Galaxy g1, Galaxy g2) {
  long x = abs(g1.x - g2.x);
  long y = abs(g1.y - g2.y);

  return x + y;
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  ifstream in(argv[1]);
  vector<string> universe;
  vector<Galaxy> galaxies;
  set<int> empty_cols, empty_rows;

  if (!in.good()) {
    in.close();
    return -1;
  }

  string line;
  while (getline(in,line)) {
    universe.push_back(line);
  }
  in.close();
  
  galaxies = find_galaxies(universe);
  empty_cols = get_empty_cols(universe);
  empty_rows = get_empty_rows(universe);

  long part1 = 0;
  long part2 = 0;
  for (int i = 0; i < galaxies.size(); ++i) {
    for (int j = i+1; j < galaxies.size(); ++j) {
      int x_min = min(galaxies[i].x, galaxies[j].x);
      int x_max = max(galaxies[i].x, galaxies[j].x);
      int y_min = min(galaxies[i].y, galaxies[j].y);
      int y_max = max(galaxies[i].y, galaxies[j].y);

      long dist = manhattan_dist(galaxies[i], galaxies[j]);
      long expansion = 0;
      // account for expansion in x direction
      expansion += count_if(empty_cols.begin(),
                            empty_cols.end(),
                            [x_min,x_max](int c) { return c > x_min && c < x_max; });
      // account for expansion in y direction
      expansion += count_if(empty_rows.begin(),
                            empty_rows.end(),
                            [y_min,y_max](int r) { return r > y_min && r < y_max; });

      part1 += dist + expansion;
      part2 += dist + expansion * 999999;
    }
  }

  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
