#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
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


  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
