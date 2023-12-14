#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include "../include/args.h"

using namespace std;

struct Race {
  int time;
  int dist;
};

vector<int> process_line(string line) {
  istringstream ss(line);
  vector<int> vals;
  string data;
  ss >> data; // get rid of header
  while (ss >> data) {
    vals.push_back(stoi(data));
  }

  return vals;
}
/*
 * x(t-x) > d // t = time of race, x = how long button held, d = dist
 *  x^2 -tx + d < 0
 *  min = (t - sqrt(t^2 - 4d))/2
 *  max = (t + sqrt(t^2 - 4d))/2
 *
 *
 */

int get_wins(Race r) {
  double t = static_cast<double>(r.time);
  double d = static_cast<double>(r.dist);

  double min = (t - sqrt(t*t - 4*d))/2;
  double max = (t + sqrt(t*t - 4*d))/2;

  int min_int = 0;
  int max_int = 0;

  double frac;
  double *intpart;

  // if min is an integer, add 1.  else, ceiling it.
  frac = modf(min,intpart);
  if (frac <= numeric_limits<double>::epsilon()) {
    min_int = static_cast<int>(min) + 1;
  }
  else {
    min_int = static_cast<int>(ceil(min));
  }
  
  // if max is an integer, subtract 1.  else, floor it.
  frac = modf(max,intpart);
  if (frac <= numeric_limits<double>::epsilon()) {
    max_int = static_cast<int>(max) - 1;
  }
  else {
    max_int = static_cast<int>(floor(max));
  }

  return max_int - min_int + 1;
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  ifstream in(argv[1]);
  vector<Race> races;

  if (in.good()) {
    string str;
    getline(in, str);
    vector<int> times = process_line(str);
    getline(in, str);
    vector<int> dists = process_line(str);

    for (int i = 0; i < times.size(); ++i) {
      Race r = { times[i], dists[i] };
      races.push_back(r);
    }
  }

  int part1 = 1;
  for (auto race : races) {
    part1 *= get_wins(race);
  }

  cout << "Part 1: " << part1 << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Clock time: " << duration.count() << " us" << endl;
  return 0;
}
