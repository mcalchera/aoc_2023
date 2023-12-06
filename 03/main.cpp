#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/args.h"


struct coord {
  int x = 0;
  int y = 0;
};

struct part { 
  int num = 0;
  bool is_part = false;
  coord location;
  int length;
};

using namespace std;

// just trying to make sure i read everything into the array correctly
void print_schematic(vector<vector<char>> schem) {
  for (int i = 0; i < schem.size(); ++i) {
    for (int j = 0; j < schem[i].size(); ++j) {
      cout << schem[i][j];
    }
    cout << endl;
  }
}

bool is_inbound(vector<vector<char>> arr, int x, int y) {
  if (x < 0 || y < 0 ) {
    return false;
  }
  if (y >= arr.size()) {
    return false;
  }
  if (x >= arr[y].size()) {
    return false;
  }
  return true;
}

// checks if a part has a symbol around it 
bool is_part(vector<vector<char>> arr, int x, int y, int width) {
  for (int i = y; i < y + 3; ++i) {
    for (int j = x; j < x + width; ++j) {
      if (is_inbound(arr, j, i)) {
        if (!isdigit(arr[i][j]) && arr[i][j] != '.') {
          return true;
        };
      }
    }
  }
  return false;
}

int gear_ratio(vector<part> parts, coord pt) {
  vector<part> vec;
  for (auto part : parts) {
    int min_x = part.location.x;
    int max_x = part.location.x + part.length;
    //left
    if (pt.y == part.location.y && pt.x == max_x) {
      vec.push_back(part);
    }
    //right
    else if (pt.y == part.location.y && pt.x+1 == min_x) {
      vec.push_back(part);
    }
    //above
    else if (pt.y - 1 == part.location.y) {
      for (int x = min_x; x < max_x; ++x) {
        if (pt.x - 1 == x || pt.x == x || pt.x+1 == x) {
          vec.push_back(part);
          break;
        }
      }
    }
    //below
    else if (pt.y + 1 == part.location.y) {
      for (int x = min_x; x < max_x; ++x) {
        if (pt.x-1 == x || pt.x == x || pt.x+1 == x) {
          vec.push_back(part);
          break;
        }
      }
    }
  }

  if (vec.size() == 2) { 
    return vec[0].num * vec[1].num;
  }

  else return 0;
}
int main (int argc, char ** argv) {
  process_args(argc, argv);

  vector<vector<char>> schematic;
  vector<part> parts;
  vector<coord> coords;

  ifstream in(argv[1]);
  
  // read file
  if (in.good()) {
    string tmpstr;
    while (getline(in,tmpstr)) {
      vector<char> line;
      for (auto ch : tmpstr) {
        line.push_back(ch);
      }
      schematic.push_back(line);
    }
  }

  // categorize each item as a part or not
  for (int i = 0; i < schematic.size(); i++) {
    for (int index = 0; index < schematic[i].size();) {
      if (isdigit(schematic[i][index])) {
        part p;
        int i_start = index;
        string tmp = "";
        //traverse string until we get a non-digit
        do {
          tmp.push_back(schematic[i][index]);
          ++index;
        } while (index < schematic[i].size() && isdigit(schematic[i][index])); 
        p.num = stoi(tmp);
        p.is_part = is_part(schematic, i_start-1, i-1, tmp.size()+2);
        p.location = {i_start,i};
        p.length = tmp.size();

        if (p.is_part) {
          parts.push_back(p);
        }
      }
      else {
        ++index;
      }
    }
  }

  for (int i = 0; i < schematic.size(); ++i) {
    for (int j = 0; j < schematic[i].size(); ++j) {
      if (schematic[i][j] == '*') {
        coord pt = {j,i};
        coords.push_back(pt);
      }
    }
  }

  int part1 = 0;
  for ( auto part : parts ) {
    part1 += (part.is_part) ? part.num : 0;
  }

  long part2 = 0;
  // loop through * and find parts that 
  for (auto coord: coords) {
    part2 += gear_ratio(parts, coord);
  }
  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
  return 0;
}
