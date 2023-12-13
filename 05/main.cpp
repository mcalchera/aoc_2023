#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include "../include/args.h"

using namespace std;

struct Mapping {
  long dest_range;
  long src_range;
  long size;

  bool is_in_dest(long x) {
    return (x >= dest_range) && (x <= dest_range + size);
  }

  bool is_in_source(long x) {
    return (x >= src_range) && (x <= src_range + size);
  }

  long do_map(long x) {
    return dest_range + (x - src_range);
  }
};

struct Map {
  string map_from;
  string map_to;
  vector<Mapping> mappings;
};

struct Seed {
  long start;
  long size;
};

vector<long> extract(string line) {
  istringstream ss(line);
  vector<long> ret;
  string data;
  while (ss >> data) {
    ret.push_back(stol(data));
  }

  return ret;
}


long part1(vector<Map> maps, long num) {
  string types[7] = { "soil", "fertilizer", "water", "light", "temperature", "humidity", "location" };
  string from = "seed";
  long key = num;
  for (long i = 0; i < 7; ++i) {
    string to = types[i];
    Map typemap = *find_if(maps.begin(), maps.end(), [to](Map map) { return map.map_to == to; });
  
    for (auto mapping : typemap.mappings) {
      if (mapping.is_in_source(key)) {
        key = mapping.do_map(key);
        break;        
      }
    }

  }
  
  return key;
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  vector<long> seeds;
  vector<Seed> seeds2;
  vector<long> locations;
  vector<Map> maps;

  ifstream in(argv[1]);

  if (in.good()) {
    istringstream ss;
    string line;
    string data;

    // first ingest seeds
    getline(in,line);
    if (line.find("seeds:") != string::npos) {
      ss.str(line);
      ss >> data; //discard "seeds:"
      while (ss >> data) {
        seeds.push_back(stol(data));
      }
    }
    while (getline(in,line)) {
      if (line.empty()) { // New mapping section
        getline(in,line);
        Map map;
        long start = 0;
        long end = line.find('-');
        map.map_from = line.substr(start, end-start);
        start = end + 4; //skip '-to-'
        end = line.find(' ', start);
        map.map_to = line.substr(start, end-start);
        maps.push_back(map);
        getline(in, line);
      }
      // Next lines until an empty line will all be numbers.
      vector<long> nums  = extract(line);
      Mapping mapping = { nums[0], nums[1], nums[2] };
      maps.back().mappings.push_back(mapping);
        
    }
     
  }
  in.close();

  for (auto seed : seeds) {
    // follow maps and get location
    locations.push_back(part1(maps, seed));
  }

  cout << "Part 1: " << *min_element(locations.begin(), locations.end()) << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
