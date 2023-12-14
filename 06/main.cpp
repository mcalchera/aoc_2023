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
  long time;
  long dist;
};

vector<long> process_line(string line) {
  istringstream ss(line);
  vector<long> vals;
  string data;
  ss >> data; // get rid of header
  while (ss >> data) {
    vals.push_back(stol(data));
  }

  return vals;
}

long process_line2(string line) {
  istringstream ss(line);
  string data;
  string val = "";
  ss >> data; // ignore header again
  while (ss >> data) {
    for (auto ch : data) {
      val.push_back(ch);
    }
  }

  return stol(val);
}
/*
 * x(t-x) > d // t = time of race, x = how long button held, d = dist
 *  x^2 -tx + d < 0
 *  min = (t - sqrt(t^2 - 4d))/2
 *  max = (t + sqrt(t^2 - 4d))/2
 *
 *
 */

long get_wins(Race r) {
  long double t = static_cast<long double>(r.time);
  long double d = static_cast<long double>(r.dist);

  long double min = (t - sqrt(t*t - 4*d))/2;
  long double max = (t + sqrt(t*t - 4*d))/2;

  long min_int = 0;
  long max_int = 0;

  double frac;
  double *intpart = new double;

  // if min is an integer, add 1.  else, ceiling it.
  frac = modf(min,intpart);
  if (frac <= numeric_limits<long double>::epsilon()) {
    min_int = static_cast<long>(min) + 1;
  }
  else {
    min_int = static_cast<long>(ceil(min));
  }
  
  // if max is an integer, subtract 1.  else, floor it.
  frac = modf(max,intpart);
  if (frac <= numeric_limits<long double>::epsilon()) {
    max_int = static_cast<long>(max) - 1;
  }
  else {
    max_int = static_cast<long>(floor(max));
  }

  delete intpart;
  return max_int - min_int + 1;
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  ifstream in(argv[1]);
  vector<Race> races;
  Race race2;
  if (in.good()) {
    string str;
    getline(in, str);
    vector<long> times = process_line(str);
    race2.time = process_line2(str);
    getline(in, str);
    vector<long> dists = process_line(str);
    race2.dist = process_line2(str);

    for (int i = 0; i < times.size(); ++i) {
      Race r = { times[i], dists[i] };
      races.push_back(r);
    }
  }

  long part1 = 1;
  for (auto race : races) {
    part1 *= get_wins(race);
  }

  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << get_wins(race2) << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Clock time: " << duration.count() << " us" << endl;
  return 0;
}
