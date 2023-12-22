#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include "../include/args.h"


using namespace std;

struct Report {
  string diagram;
  vector<int> groups;
};

vector<int> get_groups(string s) {
  int n;
  int init = 0, pos = 0;
  vector<int> vec;
  s.push_back(','); // add nondigit to end of string for ease of parsing
  string num = "";
  for (auto it = s.begin(); it < s.end(); ++it) {
    if (isdigit(*it)) {
      num.push_back(*it);
    }
    else {
      vec.push_back(stoi(num));
      num = "";
    }
  }
  return vec;
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  vector<Report> reports;

  ifstream in(argv[1]);

  if (!in.good()) {
    return 1;
  }

  string line;
  while (getline(in,line)) {
    istringstream ss(line);
    string record, groups;
    ss >> record >> groups;
    vector<int> vec = get_groups(groups);
    reports.push_back( { record, vec } );
  }

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
