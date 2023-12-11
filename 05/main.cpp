#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "../include/args.h"

using namespace std;

struct Mapping {
  int dest_range;
  int source_range;
  int size;
};

struct Map {
  string map_from;
  string map_to;
  vector<Mapping> mappings;
};

vector<int> extract(string line) {
  istringstream ss(line);
  vector<int> ret;
  string data;
  while (ss >> data) {
    ret.push_back(stoi(data));
  }

  return ret;
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  vector<int> seeds;
  vector<Map> maps;

  ifstream in(argv[1]);

  if (in.good()) {
    istringstream ss;
    string line;
    string data;
    // ingest seeds
    while (getline(in,line)) {
      if (line.find("seeds:") != string::npos) {
        ss.str(line);
        ss >> data; //discard "seeds:"
        while (ss >> data) {
          seeds.push_back(stoi(data));
        }
        getline(in,line);
      }

      if (line.empty()) { // New mapping section
        getline(in,line);
        Map map;
        int start = 0;
        int end = line.find('-');
        map.map_from = line.substr(start, end-start);
        start = end + 4; //skip '-to-'
        end = line.find(' ', start);
        map.map_to = line.substr(start, end-start);
        maps.push_back(map);
        getline(in, line);
      }
      // Next lines until an empty line will all be numbers.
      vector<int> nums  = extract(line);
      Mapping mapping = { nums[0], nums[1], nums[2] };
      maps.back().mappings.push_back(mapping);
        
    }
     
  }

  in.close();
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
